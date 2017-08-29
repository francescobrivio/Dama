#!/usr/bin/perl

##### Packages #####

use IPC::Open2;
use IO::Handle;
use IO::Pipe;

use Tk;
use Tk::Dialog;
use Tk::LabFrame;
use Tk::PNG;
use utf8;

require 'Grid.pl';
require 'Routines.pl';


##### Global Variables #####
#my $welcomeMessage = "Welcome";
my $input = '';
@buttons;
@positions ;
$team;
$CPU;

#### Main #####

# Pipes
pipe (READFROM_TK, WRITETO_C);
pipe (READFROM_C , WRITETO_TK);
WRITETO_C->autoflush(1);
WRITETO_TK->autoflush(1);

# Forking;
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
    my $pid = shift;
    chomp($pid_cpp = <READFROM_C>);
    #print "Father PID: $$ - Child PID: $pid \n";
    
    # MainWindow
    my $mw = MainWindow->new;
    $mw->geometry("800x500");
    $mw->title ("Test Dama");

    $dama_bianca = $mw->Photo(-file=> "../../Images/dama_bianca.png");
    $dama_bianca_scaled = $mw->Photo(-file=>"");
    $dama_bianca_scaled->copy($dama_bianca, -subsample=>2,2);

    $dama_nera = $mw->Photo(-file=> "../../Images/dama_nera.png");
    $dama_nera_scaled = $mw->Photo(-file=>"");
    $dama_nera_scaled->copy($dama_nera, -subsample=>2,2);

    $damone_bianco = $mw->Photo(-file=> "../../Images/damone_bianco.png");
    $damone_bianco_scaled = $mw->Photo(-file=>"");
    $damone_bianco_scaled->copy($damone_bianco, -subsample=>2,2);

    $damone_nero = $mw->Photo(-file=> "../../Images/damone_nero.png");
    $damone_nero_scaled = $mw->Photo(-file=>"");
    $damone_nero_scaled->copy($damone_nero, -subsample=>2,2);

    $dama_empty = $mw->Photo(-file=> "../../Images/dama_empty.png");
    $dama_empty_scaled = $mw->Photo(-file=>"");
    $dama_empty_scaled->copy($dama_empty, -subsample=>2,2);

    # menuFrame
    my $menuframe = $mw->Frame(-background=>"aquamarine4", -bd=>2, -relief=>'raised');
    $menuframe->pack(-side=>"top", -fill=>"x");

        my $filemenu = $menuframe->Menubutton(-text=>'File', -activebackground=>"aquamarine", -foreground=>"black");
        $filemenu->command(-label=>"New Game", -command=>\&newGame);
        $filemenu->command( -label=>"Quit", -command=>[\&quit,$pid,$pid_cpp]);
        $filemenu->pack(-side=>"left", -fill=>"x");

        my $quitmenu = $menuframe->Button( -text=>"Quit", -command=>[\&quit,$$,$pid,$pid_cpp])->pack;
        $quitmenu->pack(-side=>"right");

    # logFrame
    my $logframe = $mw->LabFrame(-label=>"Moves Log", -bd=>2, -relief=>'raised', -padx=>"10");
    $logframe->pack(-side=>"right", -fill=>"both");
    
        $log = $logframe->Scrolled("Text", -scrollbars => 'e', -width=>40, -height=>25, -bg=>"black", -fg=>"white");
        $log->tagConfigure('red'  , -foreground=>"red");
        $log->tagConfigure('green', -foreground=>"green");
        $log->tagConfigure('under', -underline=>1);
        $log->insert('end', "----------- WELCOME TO DAMA -----------\n", 'green');
        $log->insert('end', " Remeber, WHITE always starts first.\n");
        $log->insert('end', " Select \"File->NewGame\" to begin.\n");
        $log->insert('end', "---------------------------------------\n", 'green');

        #$pawns_left = $logframe->Text(-width=>43, -height=>2, -bg=>"black", -fg=>"white")->pack();
        #$pawns_left->tagConfigure('title'  , -foreground=>"green");
        #$pawns_left->insert('end', " --------------- PAWNS LEFT -------------- \n", 'title');
    
        $pawns_left_title = $logframe->Label(-text=>' --------------- PAWNS LEFT -------------- ');
        #s$pawns_left_title->pack();

        $nWhite_label = $logframe->Label(-text=>'White');
        $nWhite_entry = $logframe->Entry(-width=>3, -state=>'disabled');
        $nBlack_label = $logframe->Label(-text=>'Black');
        $nBlack_entry = $logframe->Entry(-width=>3, -state=>'disabled');
    
        $user_move = $logframe->Entry(-width=>17);
        #$user_move->pack(-side=>"left");

        my $printing = $logframe->Button(-text=>"Enter Move",, -width=>9, -command=>sub{
                                        print WRITETO_C $user_move->cget(-textvariable)."\n";
                                        chomp($flag_msg = <READFROM_C>);
                                        @flag_split = split //, $flag_msg;
                                        if ($flag_msg == 1)
                                        {
                                          @log_move = split //, $user_move->cget(-textvariable);
                                          if (@flag_split[1] eq 'w')
                                          {
                                            $log->insert('end', " Player1: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
                                            $log->see('end');
                                          }
                                          elsif (@flag_split[1] eq 'b')
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
										  sleep(2);
										  print WRITETO_C "auto\n";
										  print "auto passato a c++\n";
										  chomp($newPositions = <READFROM_C>);
										  @positions = split//,$newPositions;
										  &loopOnButtons(\@positions);
										  chomp($endGame = <READFROM_C>);
										  if($endGame == 1)
                                          {
										    print "END GAME\n";
										  }
                                        }
                                        &countPawns(\$newPositions);
                                        });
        #$printing->pack(-side=>"right");
    
        my $clearing = $logframe->Button(-text=>"Clear Move", -width=>8, -command=>sub{$user_move->delete(0,30);} );
        #$clearing->pack(-side=>"right");

        $log                ->pack(-side => 'top', -anchor => 'n', -fill=>'x');
        $pawns_left_title   ->pack();
        $nWhite_label       ->pack();
        $nWhite_entry       ->pack();
        #$nBlack_label       ->pack();
        #$nBlack_entry       ->pack();
        $user_move          ->pack(-side => 'left', -fill=>'x');
        $clearing           ->pack(-side => 'left', -fill=>'x');
        $printing           ->pack(-side => 'left', -fill=>'x');


    # gridFrame
    $gridframe = $mw->LabFrame(-label=>"Dama", -bd=>2, -relief=>'raised');
    $gridframe->pack(-side=>"left", -fill=>"both", -expand=>1, -pady=>'0');
    
        $d0 = $mw->Dialog(-title=>"",-text=>"Scegli la modalità di gioco!", -popover=>$gridframe, -buttons=>[]);
        my $PvsP = $d0->Radiobutton(-text=>'Player vs Player', -value=>0, -variable=>\$CPU, -command=>[\&gameMode, 0]);
        $PvsP->pack();
        my $PvsC = $d0->Radiobutton(-text=>'Player vs CPU', -value=>1, -variable=>\$CPU, -command=>[\&gameMode, 1]);
        $PvsC->pack();

        $d1 = $mw->Dialog(-title=>"",-text=>"Scegli il colore della tua squadra!", -popover=>$gridframe, -buttons=>[]);
        my $black_team = $d1->Radiobutton(-text=>'black', -value=>'black', -variable=>\$team, -image=> $dama_nera_scaled  , -command=>[\&beginGame,"black\n"]);
        $black_team->pack();
        my $white_team = $d1->Radiobutton(-text=>'white', -value=>'white', -variable=>\$team, -image=> $dama_bianca_scaled, -command=>[\&beginGame,"white\n"]);
        $white_team->pack();

    ##### Loop #####
    $mw->MainLoop;

    exit(0);
}

# TKthread
sub CPPthread
{
    my $pid = shift;
    die "Cannot fork $!\n" unless defined $pid;
    #print "Child PID: $$ \n";
    
    ####
    #print "Scegli il colore della tua squadra!";
    #chomp ($team = <READFROM_TK>);
    #print "team: $team\n";
    
    #declare the IPC::Open2 connection to dama.exe
    my $Reader;
    my $Writer;
    my $pid2 = open2($Reader,$Writer, "../cpp/dama.exe");
    print WRITETO_TK $pid2."\n";

    $Writer->autoflush(1);
    $Reader->autoflush(1);
    #print "Open PID Dama: $pid2 \n";

    #print "Scegli il colore della tua squadra!"; 
    chomp ($team = <READFROM_TK>);
    #print "team: $team\n";

    # starting positions
    print $Writer("$team\n");
    my $new_positions = <$Reader>;
    #print "cazzo le position:  $new_positions \n";
    print WRITETO_TK $new_positions;#."\n";

    my $endgame = 0;
    my $move = "";
    
    while($endgame == 0)
    {
      chomp ($move = <READFROM_TK>);
      #print $move." arrivata a c++\n";
      print $Writer("$move\n");
      $flag_fromCPP  = <$Reader>;
      $new_positions = <$Reader>;
      #print "cazzo le position loop:  $new_positions \n";
      print WRITETO_TK $flag_fromCPP;
      print WRITETO_TK $new_positions;

      $endgame = <$Reader>;
      #print "endgame: $endgame\n";
      print WRITETO_TK $endGame."\n";
      #chomp ($turn = <READFROM_TK>);
    }
    
    close($Writer);
    close($Reader);
    
    exit(0);

}


