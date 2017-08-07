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
@fake_positions = qw/w w e w e e e B
                     b e w e b e w W
                     e w b e w e b w
                     w e b e b W B e
                     e w w w e e e B
                     b e w e b e w W
                     e w b e w e b w
                     w e b e b W B e/;
print "fake_positions: @fake_positions \n" ;
                  #= (0,0,0,0,0,0,0,0, # 1a, 1b ....
                  # 1,1,1,1,1,1,1,2, # 2a, 2b ....
                  # 1,2,2,0,0,0,0,2,
                  # 0,2,0,0,1,2,0,2,
                  # 0,0,2,2,1,0,0,2,
                  # 0,0,2,1,1,2,0,2,
                  # 2,1,1,2,0,2,1,1,
                  # 2,0,0,2,1,1,2,2); # ... 8h

#### Main #####

# Pipes
pipe ($READFROM_TK , $WRITETO_CPP); # in CPP legge da TK, e da TK scrive a CPP
pipe ($READFROM_CPP, $WRITETO_TK ); # in TK legge da CPP, e da CPP scrive a TK
$WRITETO_CPP->autoflush(1);
$WRITETO_TK->autoflush(1);

# Forking;
if (my $pid = fork)
{
    close $READFROM_TK;
    close $WRITETO_TK;
    &TKthread($pid);
    #close READFROM_CPP;
    #close WRITETO_CPP;
}
else
{
    close $READFROM_CPP;
    close $WRITETO_CPP;
    &CPPthread($pid);
    #close READFROM_TK;
    #close WRITETO_TK;
}

# TKthread
sub TKthread
{
    my $pid = shift;
    print "Father PID: $$ - Child PID: $pid \n";
    
    # MainWindow
    my $mw = MainWindow->new;
    $mw->geometry("800x500");
    $mw->title ("Test Dama");

    $dama_bianca = $mw->Photo(-file=> "../Images/dama_bianca.png");
    $dama_bianca_scaled = $mw->Photo(-file=>"");
    $dama_bianca_scaled->copy($dama_bianca, -subsample=>2,2);

    $dama_nera = $mw->Photo(-file=> "../Images/dama_nera.png");
    $dama_nera_scaled = $mw->Photo(-file=>"");
    $dama_nera_scaled->copy($dama_nera, -subsample=>2,2);
    
    $damone_bianco = $mw->Photo(-file=> "../Images/damone_bianco.png");
    $damone_bianco_scaled = $mw->Photo(-file=>"");
    $damone_bianco_scaled->copy($damone_bianco, -subsample=>2,2);

    $damone_nero = $mw->Photo(-file=> "../Images/damone_nero.png");
    $damone_nero_scaled = $mw->Photo(-file=>"");
    $damone_nero_scaled->copy($damone_nero, -subsample=>2,2);


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

        my $test_move = $logframe->Button(-text=>"change image" #,-command=>[\&loopOnButtons,\@fake_positions]);
                                                                 , -command=>sub{chomp($newPosition = <$READFROM_CPP>);
                                                                               print "prima: $newPositions \n";
                                                                               @fake_positions = split//,$newPositions;
                                                                               print "dopo: @newPositions \n";
                                                                               &loopOnButtons(\@fake_positions)});
        $test_move->pack();
        #$mw->fileevent($READFROM_CPP, 'readable', [\&changeImage,$test_move]);

        #my $test_move2 = $logframe->Button(-text=>"", -image=> $dama_nera_scaled, -command=>sub{print $WRITETO_CPP "black\n;"});
        #$test_move2->pack();
    
        #my $test_move3 = $logframe->Button(-text=>"", -image=> $dama_bianca_scaled, -command=>sub{print $WRITETO_CPP "white\n;"});
        #$test_move3->pack();

        my $log = $logframe->Label(-text=>'qui il log vero', -borderwidth=>3, -relief=>"sunken", -fg=>"white", -bg=>"black");
        $log->pack(-fill=>"x");

        $user_move = $logframe->Entry();
        $user_move->pack(-side=>"left");

        my $printing = $logframe->Button(-text=>"Enter Move", -command=>sub{print "passalo a cpp\n"} );
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
    #chomp ($team = <$READFROM_TK>);
    $team = "black";
    print "team: $team\n";
    
    my $Reader;
    my $Writer;
    my $pid2 = open2($Reader,$Writer, "../Davide_codes/dama.exe");
    print "Open PID: $pid2 \n";
    
    print $Writer("$team\n");
    $str = <$Reader>;
    print "cppthread: $str \n";
    #print "split: ",split(//,$str), "\n";
    #@fake_positions = split//,$str ;
    #print "split: $str \n";
    #join(' ', split(//,$str));
    print $WRITETO_TK "prova";#\$str;
    
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
    
    close($Writer);
    close($Reader);
    
    exit(0);

}


