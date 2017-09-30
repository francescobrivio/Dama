#!/usr/bin/perl

################# Packages #################
# Perl includes
use IPC::Open2;
use IO::Handle;
use IO::Pipe;

use Tk;
use Tk::Dialog;
use Tk::LabFrame;
use Tk::PNG;
use utf8;

# Ad hoc includes
require 'Grid.pl';
require 'Routines.pl';

################ Main #################

# Global Variables
my $input = '';
@buttons;
@positions ;
$team;
$CPU=0;
$CPUgoON=1;

# Pipes declaration
pipe (READFROM_TK, WRITETO_C);
pipe (READFROM_C , WRITETO_TK);
WRITETO_C->autoflush(1);
WRITETO_TK->autoflush(1);

# Forking
if (my $pid = fork)
{
    close READFROM_TK;
    close WRITETO_TK;
    &TKthread($pid);
}
else
{
    close READFROM_C;
    close WRITETO_C;
    &CPPthread($pid);
}

# TKthread
sub TKthread
{
    # Fork sanity check
    my $pid = shift;
    chomp(my $pid_cpp = <READFROM_C>);
    
    # Tk MainWindow
    $mw = MainWindow->new;
    $mw->geometry("800x650");
    $mw->title ("Test Dama");

    # Images of the pawns
    my $dama_bianca = $mw->Photo(-file=> "../../Images/dama_bianca.png");
    $dama_bianca_scaled = $mw->Photo(-file=>"");
    $dama_bianca_scaled->copy($dama_bianca, -subsample=>2,2);

    my $dama_nera = $mw->Photo(-file=> "../../Images/dama_nera.png");
    $dama_nera_scaled = $mw->Photo(-file=>"");
    $dama_nera_scaled->copy($dama_nera, -subsample=>2,2);

    my $damone_bianco = $mw->Photo(-file=> "../../Images/damone_bianco_2.png");
    $damone_bianco_scaled = $mw->Photo(-file=>"");
    $damone_bianco_scaled->copy($damone_bianco, -subsample=>2,2);

    my $damone_nero = $mw->Photo(-file=> "../../Images/damone_nero_2.png");
    $damone_nero_scaled = $mw->Photo(-file=>"");
    $damone_nero_scaled->copy($damone_nero, -subsample=>2,2);

    my $dama_empty = $mw->Photo(-file=> "../../Images/dama_empty.png");
    $dama_empty_scaled = $mw->Photo(-file=>"");
    $dama_empty_scaled->copy($dama_empty, -subsample=>2,2);

    # menuFrame
    my $menuframe = $mw->Frame(-background=>"aquamarine4", -bd=>2, -relief=>'raised');
    $menuframe->pack(-side=>"top", -fill=>"x");

    # Menu bar
    my $filemenu = $menuframe->Menubutton(-text=>'File', -activebackground=>"aquamarine", -foreground=>"black");
    $filemenu->command(-label=>"New Game", -command=>\&newGame);
    $filemenu->command(-label=>"Help", -command=>\&showHelpPanel);
    $filemenu->command( -label=>"Quit", -command=>[\&QuitConfirm]); #\&quit,$$,$pid,$pid_cpp
    $filemenu->pack(-side=>"left", -fill=>"x");
    
    # Quit button
    my $quitmenu = $menuframe->Button( -text=>"Quit", -command=>[\&QuitConfirm])->pack;
    $quitmenu->pack(-side=>"right");
    
    # logFrame
    my $logframe = $mw->LabFrame(-label=>"", -bd=>2, -relief=>'raised', -padx=>"10");
    $logframe->pack(-side=>"right", -fill=>"both");
    
    $pawns_left_title = $logframe->Label(-text=>"\n ------------------- PAWNS LEFT ------------------ \n")->pack();
    my $pawnsframe  = $logframe->Frame()->pack();
    my $loglogframe = $logframe->Frame()->pack();
    
    # Simple text
    $log_title = $loglogframe->Label(-text=>"\n\n ------------------- MOVES LOG ------------------ \n")->pack();
    
    # Scrolled button to keep the log of the moves
    $log = $loglogframe->Scrolled("Text", -scrollbars => 'e', -width=>40, -height=>25, -bg=>"black", -fg=>"white")->pack();
    $log->tagConfigure('red'  , -foreground=>"red");
    $log->tagConfigure('green', -foreground=>"green");
    $log->tagConfigure('under', -underline=>1);
    $log->insert('end', "----------- WELCOME TO DAMA -----------\n", 'green');
    $log->insert('end', " Select \"File->NewGame\" to begin and\n");
    $log->insert('end', " remember, WHITE always starts first.\n");
    #$log->insert('end', "\n");
    #$log->insert('end', "-INSTRUCTIONS: click on the pawn to\n");
    #$log->insert('end', " select it and then click where you\n");
    #$log->insert('end', " you want to move it. Finally just\n");
    #$log->insert('end', " click \"Enter Move\" \n");
    $log->insert('end', "---------------------------------------\n", 'green');

    # Counters to show the number of pawns remaining
    $nWhite_label = $pawnsframe->Label(-text=>'White:', -image=>$dama_bianca_scaled)->pack(-side=>'left');
    $nWhite_entry = $pawnsframe->Entry(-width=>3, -state=>'disabled', -disabledforeground=>'black', -disabledbackground=>'white')->pack(-side=>'left');
    $nWhite_label = $pawnsframe->Label(-text=>'           ')->pack(-side=>'left');
    $nBlack_label = $pawnsframe->Label(-text=>'Black:', -image=> $dama_nera_scaled)->pack(-side=>'right');
    $nBlack_entry = $pawnsframe->Entry(-width=>3, -state=>'disabled', -disabledforeground=>'black', -disabledbackground=>'white')->pack(-side=>'right');


    #my $movesframe  = $logframe->Frame()->pack();  
    my $movesframe = $mw->LabFrame(-label=>"User Move", -bd=>2, -relief=>'raised');
    $movesframe->pack(-side=>"bottom", -fill=>"both");

    # Simple text
    #$separation_line = $movesframe->Label(-text=>"\n\n ------------------- USER MOVE ------------------ \n")->pack();    
    
    # Container for the move
    $user_move = $movesframe->Entry(-width=>25)->pack(-side => 'left', -fill=>'x');
    
    # Delete the move
    my $clearing = $movesframe->Button(-text=>"Clear Move", -width=>8, -command=>sub{&restoreColors();$user_move->delete(0,30);} )->pack(-side => 'left', -fill=>'x');

    # Confirm the move
    my $printing = $movesframe->Button(-text=>"Enter Move", -width=>9, 
				       -command=>sub{
					   if(@buttons[0] != 0 and 
					      $user_move->cget(-textvariable) ne ''){ 
					       &doTheMove($user_move->cget(-textvariable)."\n");
					       $mw->update;
					       if($CPU==1 and $CPUgoON==1){
						   sleep(1); 
						   &doTheMove("auto\n");}
					   }
				       })->pack(-side => 'left', -fill=>'x');
    
    my $giveUp_buttom = $movesframe->Button(-text=>"Give Up", -width=>9, 
					    -command=>sub{
						if(@buttons[0] != 0){&GiveUpConfirm();}
					    })->pack(-side => 'left', -fill=>'x'); 
=pod
                                        print WRITETO_C $user_move->cget(-textvariable)."\n";
            
                                        chomp($flag_msg = <READFROM_C>);
                                        @flag_split = split //, $flag_msg;
                                        if ($flag_msg == 1)
                                        {
                                          @log_move = split //, $user_move->cget(-textvariable);
                                          if (@flag_split[1] eq 'w' || @flag_split[1] eq 'W')
                                          {
                                            $log->insert('end', " Player1: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
                                            $log->see('end');
                                          }
                                          elsif (@flag_split[1] eq 'b' || @flag_split[1] eq 'B')
                                          {
                                            $log->insert('end', " Player2: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
                                            $log->see('end');
                                          }
                                          else
                                          {
                                            $log->insert('end', " PC: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
                                            $log->see('end');
                                          }
                                        }
                                        else
                                        {
                                          $log->insert('end', " Move not allowed!Try again!\n", 'red');
                                          $log->see('end');
                                        }
            
									    chomp($newPositions = <READFROM_C>);
									    @positions = split//, $newPositions;            
									    &loopOnButtons(\@positions);
                                        &countPawns(\@positions);
									    chomp($endGame = <READFROM_C>);
									    $user_move->delete(0,30);
            
									    if($endGame == 1)
                                        {
										  print "END GAME\n";
                                          $log->insert('end',"---------- GAME FINISHED!! ----------\n", 'red');
                                          $log->insert('end'," who's the winner??\n");
                                          $log->see('end');
									    }

									    if($CPU==1)
                                        {
										  $mw->update;
										  sleep(1);
										  print WRITETO_C "auto\n";
										  #print "auto passato a c++\n";
										  chomp($newPositions = <READFROM_C>);
										  @positions = split//,$newPositions;
										  &loopOnButtons(\@positions);
                                          &countPawns(\@positions);
										  chomp($endGame = <READFROM_C>);
										  if($endGame == 1)
                                          {
										    print "END GAME\n";
                                            $log->insert('end',"---------- GAME FINISHED!! ----------\n", 'red');
                                            $log->insert('end'," who's the winner??\n");
                                            $log->see('end');
										  }
                                        }
=cut

    # gridFrame
    $gridframe = $mw->LabFrame(-label=>"DamaGame", -bd=>2, -relief=>'raised');    
    $gridframe->pack(-side=>"left", -fill=>"both", -expand=>1, -pady=>'0');
    
    # Dialog for game mode decision
    #$d0 = $mw->Dialog(-text=>"Choose the game mode!", -popover=>$gridframe, -buttons=>[]);
    #my $PvsP = $d0->Radiobutton(-text=>'Player vs Player', -value=>0, -variable=>\$CPU, -command=>[\&gameMode, 0]);
    #$PvsP->pack();
    #my $PvsC = $d0->Radiobutton(-text=>'Player vs CPU', -value=>1, -variable=>\$CPU, -command=>[\&gameMode, 1]);
    #$PvsC->pack();

    # Dialog for team color decision
    #$d1 = $mw->Dialog(-text=>"Choose the color of you team!", -popover=>$gridframe, -buttons=>[]);
    #my $black_team = $d1->Radiobutton(-text=>'black', -value=>'black', -variable=>\$team, -image=> $dama_nera_scaled  , -command=>[\&beginGame,"black\n",$CPU]);
    #$black_team->pack();
    #my $white_team = $d1->Radiobutton(-text=>'white', -value=>'white', -variable=>\$team, -image=> $dama_bianca_scaled, -command=>[\&beginGame,"white\n",$CPU]);
    #$white_team->pack();
    

    # Tk MainLoop
    $mw->MainLoop;

    exit(0);
}

# TKthread
sub CPPthread
{
    # Fork sanity check
    my $pid = shift;
    die "Cannot fork $!\n" unless defined $pid;
    
    # Declare the IPC::Open2 connection to dama.exe
    my $Reader;
    my $Writer;
    my $pid2 = open2($Reader,$Writer, "../cpp/dama.exe");
    print WRITETO_TK $pid2."\n";
    $Writer->autoflush(1);
    $Reader->autoflush(1);

    # Declare flags and useful variables     
    my $endgame = 0;
    my $endmatch = 0;
    my $move = "";
    my $team = "";

    while($endgame == 0)
    {
      $endmatch = 0;
      # Read the team chosen from Tk in order to initialize the game
      chomp ($team = <READFROM_TK>);
      
      # Starting positions
      print $Writer("$team\n");
      my $new_positions = <$Reader>;
      print WRITETO_TK $new_positions;#."\n";
    
      # Main loop for the game
      while($endmatch == 0)
      {
	# Read the move from Tk
	chomp($move = <READFROM_TK>);
      
        # Pass the move to exe
        print $Writer("$move\n");
      
        # Read move_flag, updated_positions and endgame_flag from exe
        my $pos_fromCPP   = <$Reader>;
        my $flag_fromCPP  = <$Reader>;
	my $error_fromCPP = <$Reader>;
        my $new_positions = <$Reader>;
        $endmatch         = <$Reader>;
	my $winner        = <$Reader>;
        $endgame          = <$Reader>;

	# Pass move_flag, updated_positions and endgame_flag to Tk
        print WRITETO_TK $endgame;
        print WRITETO_TK $endmatch;
	print WRITETO_TK $winner;
        print WRITETO_TK $pos_fromCPP;
        print WRITETO_TK $flag_fromCPP;
	print WRITETO_TK $error_fromCPP;
        print WRITETO_TK $new_positions;
	
	if(($move ne 'end') and ($move ne 'quit'))
	{$endmatch = 0;}
      }
    }
    # Close the pipes to exe
    close($Writer);
    close($Reader);
    
    exit(0);
}

