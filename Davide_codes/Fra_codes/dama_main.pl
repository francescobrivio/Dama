#!/usr/bin/perl

##### Packages #####

use IPC::Open2;
use IO::Handle;
use IO::Pipe;

use Tk;
use Tk::Dialog;
use Tk::LabFrame;
use Tk::PNG;

require 'Grid.pl';
require 'Routines.pl';


##### Global Variables #####
$welcomeMessage = "Welcome";
my $input = '';
@buttons;
@positions ; #= (0,0,0,0,0,0,0,0, # 1a, 1b ....
                  # 1,1,1,1,1,1,1,2, # 2a, 2b ....
                  # 1,2,2,0,0,0,0,2,
                  # 0,2,0,0,1,2,0,2,
                  # 0,0,2,2,1,0,0,2,
                  # 0,0,2,1,1,2,0,2,
                  # 2,1,1,2,0,2,1,1,
                  # 2,0,0,2,1,1,2,2); # ... 8h

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
    print "Father PID: $$ - Child PID: $pid \n";
    
    #print WRITETO_C "cazzo\n;";
    #chomp (my $newPosition = <READFROM_C>);
    #print "cazzo in $newPosition   succhia!!!";
    
    # MainWindow
    my $mw = MainWindow->new;
    $mw->geometry("800x500");
    $mw->title ("Test Dama");

    $dama_bianca = $mw->Photo(-file=> "dama_bianca.png");
    $dama_bianca_scaled = $mw->Photo(-file=>"");
    $dama_bianca_scaled->copy($dama_bianca, -subsample=>2,2);

    $dama_nera = $mw->Photo(-file=> "dama_nera.png");
    $dama_nera_scaled = $mw->Photo(-file=>"");
    $dama_nera_scaled->copy($dama_nera, -subsample=>2,2);


    # menuFrame
    my $menuframe = $mw->Frame(-background=>"aquamarine4", -bd=>2, -relief=>'raised');
    $menuframe->pack(-side=>"top", -fill=>"x");

        my $filemenu = $menuframe->Menubutton(-text=>'File', -activebackground=>"aquamarine", -foreground=>"black");
        $filemenu->command(-label=>"New Game", -command=>\&newGame);
        $filemenu->command( -label=>"Quit", -command=>[\&quit,$pid]);
        $filemenu->pack(-side=>"left", -fill=>"x");

            my $firstPopUp = $mw->Dialog(-text=>"First Dialog", -popover=>$mw);

        my $quitmenu = $menuframe->Button( -text=>"Quit", -command=>[\&quit,$pid])->pack;
        $quitmenu->pack(-side=>"right");

    # logFrame
    my $logframe = $mw->LabFrame(-label=>"Moves Log", -bd=>2, -relief=>'raised', -padx=>"10");
    $logframe->pack(-side=>"right", -fill=>"both");

        my $test_move = $logframe->Button(-text=>"change image", -command=>sub{chomp ($newPositions = <READFROM_C>);
                                                                               #print "prima: $newPositions \n";
                                                                               @positions = split//,$newPositions;
                                                                               #print "dopo: $newPositions\n";
                                                                               &loopOnButtons(\@positions)}); #[\&loopOnButtons,\@fake_positions]);
        $test_move->pack();

        my $test_move2 = $logframe->Button(-text=>"", -image=> $dama_nera_scaled, -command=>sub{print WRITETO_C "black\n"});
        $test_move2->pack();
    
        my $test_move3 = $logframe->Button(-text=>"", -image=> $dama_bianca_scaled, -command=>sub{print WRITETO_C "white\n"});
        $test_move3->pack();

        my $log = $logframe->Label(-text=>'qui il log vero', -borderwidth=>3, -relief=>"sunken", -fg=>"white", -bg=>"black");
        $log->pack(-fill=>"x");

        $user_move = $logframe->Entry();
        $user_move->pack(-side=>"left");

        my $printing = $logframe->Button(-text=>"Enter Move", -command=>sub{print WRITETO_C $user_move->cget(-textvariable)."\n";
									    print $user_move->cget(-textvariable)." passato a c++\n"});
        $printing->pack(-side=>"right");
    
        my $clearing = $logframe->Button(-text=>"Clear Move", -command=>sub{$user_move->delete(0,30);} );
        $clearing->pack(-side=>"right");

    # gridFrame
    $gridframe = $mw->LabFrame(-label=>"Dama", -bd=>2, -relief=>'raised');
    $gridframe->pack(-side=>"left", -fill=>"both", -expand=>1, -pady=>'0');

        $testext = $gridframe->Label(-text=>'Welcome');
        $testext->pack();

        $d1 = $mw->Dialog(-text=>"Begin Game", -popover=>$gridframe);
            my $begingame = $d1->Button(-text=>"Begin", -command=>\&beginGame);
            $begingame->pack();
            my $endgame = $d1->Button(-text=>"Quit", -command=>[\&clear, $gridframe]);    # <- qui user sub{....}
            $endgame->pack();

    ##### Loop #####
    $mw->MainLoop;

    exit(0);
}

# TKthread
sub CPPthread
{
    my $pid = shift;
    die "Cannot fork $!\n" unless defined $pid;
    print "Child PID: $$ \n";
    
    ####
    print "Scegli il colore della tua squadra!";
    chomp ($team = <READFROM_TK>);
    print "team: $team\n";
    
    my $Reader;
    my $Writer;
    my $pid2 = open2($Reader,$Writer, "../Davide_codes/dama.exe");
    print "Open PID Dama: $pid2 \n";
    
    print $Writer("$team\n");
    my $new_positions = <$Reader>;
    print "cazzo le position:  $new_positions \n"; 
    print WRITETO_TK $new_positions."\n";

    my $endgame = 0;
    my $move = "";
    
    print "INIZIO LOOP";
    while($endgame == 0)
    {
	chomp ($move = <READFROM_TK>);
	print $move." arrivata a c++\n";
	print $Writer("$move\n");
	$new_positions = <$Reader>;
	print "cazzo le position loop:  $new_positions \n";
	print WRITETO_TK $new_positions."\n";
    }	
	###### actions #####
    #my $question = <$Reader>;
    #print $question;
    #my $question2 = <$Reader>;
    #print $question2;

    #print $Writer($input);

    #my $pos = <$Reader>;
    #print "Position: $position \n";

    #my $great = <$Reader>;
    #print $great;
    
    close(Writer);
    close(Reader);
    
    exit(0);

}


