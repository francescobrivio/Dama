#!/usr/bin/perl

##### Packages #####
use Tk;
use Tk::Dialog;
use Tk::LabFrame;
use IPC::Open2;
use Tk::PNG;

require 'Grid.pl';
require 'Routines.pl';

##### Variables #####
$welcomeMessage = "Welcome";


##### Main #####
my $mw = MainWindow->new;
$mw->geometry("700x500");
$mw->title ("Test Dama");

$img_dama_bianca = $mw->Photo(-file=> "dama_bianca.png", -height=>'2', -width=>'2');
#$dama_bianca = $img_dama_bianca->copy($img_dama_bianca, -shrink=>);

# mwFrame
$menuframe = $mw->Frame(-background=>"aquamarine4", -bd=>2, -relief=>'raised');
$menuframe->pack(-side=>"top", -fill=>"x");

    $filemenu = $menuframe->Menubutton(-text=>'File', -activebackground=>"aquamarine", -foreground=>"black");
    $filemenu->command(-label=>"New Game", -command=>\&newGame);
    $filemenu->command( -label=>"Quit", -command=>\&quit);
    $filemenu->pack(-side=>"left", -fill=>"x");

        $firstPopUp = $mw->Dialog(-text=>"First Dialog", -popover=>$mw);

    $quitmenu = $menuframe->Button( -text=>"Quit", -command=>\&quit)->pack;
    $quitmenu->pack(-side=>"right");

# logFrame
$logframe = $mw->LabFrame(-label=>"Moves Log", -bd=>2, -relief=>'raised', -padx=>"10");
$logframe->pack(-side=>"right", -fill=>"both");

    $test_move = $logframe->Button(-text=>"white move in 8a", -command=>\&white_move);
    $test_move->pack();

    $test_move2 = $logframe->Button(-text=>"black move in 8b", -command=>\&black_move);
    $test_move2->pack();

    $log = $logframe->Label(-text=>'qui il log vero', -borderwidth=>3, -relief=>"sunken", -fg=>"white", -bg=>"black");
    $log->pack(-fill=>"x");

    $user_move = $logframe->Entry(-textvariable=>\$userEntry);
    $user_move->pack(-side=>"left");

    $printing = $logframe->Button(-text=>"Enter Move", -command=>\&printFunc);
    $printing->pack(-side=>"right");

# gridFrame
$gridframe = $mw->LabFrame(-label=>"Dama", -bd=>2, -relief=>'raised');
$gridframe->pack(-side=>"left", -fill=>"both", -expand=>1, -pady=>'0');

    $testext = $gridframe->Label(-text=>'Welcome');
    $testext->pack();



##### Loop #####
$mw->MainLoop;

##### Functions #####
sub BEGIN
{
	print "Starting Game...\n";
}

sub quit
{
    print "Quitting Game...\n";
    exit(0);
}


