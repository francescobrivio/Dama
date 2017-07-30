#!/usr/bin/perl

##### Packages #####
use Tk;
use Tk::LabFrame;

require 'Grid.pl';

##### Main #####

my $mw = MainWindow->new;
$mw->geometry("700x400");
$mw->title ("Test Dama");

$menuframe = $mw->Frame(-background=>"aquamarine4", -bd=>2, -relief=>'raised');
$menuframe->pack(-side=>"top", -fill=>"x");

    $filemenu = $menuframe->Menubutton(-text=>'File', -activebackground=>"aquamarine", -foreground=>"black");
    $filemenu->command(-label=>"New Game", -command=>\&newGame);
    #$filemenu->separator();
    $filemenu->command( -label=>"Another Quit", -command=>\&finishGame);
    $filemenu->pack(-side=>"left", -fill=>"x");

    $quitmenu = $menuframe->Button( -text=>"Quit", -command=>\&finishGame)->pack;
    $quitmenu->pack(-side=>"right");

$logframe = $mw->LabFrame(-label=>"Moves Log", -bd=>2, -relief=>'raised', -padx=>"40");
$logframe->pack(-side=>"right", -fill=>"both");

    $log = $logframe->Label(-text=>'qui il log vero');
    $log->pack(-side=>"top");

    $test_move = $logframe->Button(-text=>"test a move in 8a \n(not working)", -command=>\&moveVal);
    $test_move->pack();

$gridframe = $mw->LabFrame(-label=>"Dama", -bd=>2, -relief=>'raised');
$gridframe->pack(-side=>"left", -fill=>"both", -expand=>1, -pady=>'0');

    $testext = $gridframe->Button(-text=>"newGame", -command=>\&newGame);
    $testext->pack();



##### Loop #####
$mw->MainLoop;

##### Functions #####
sub BEGIN
{
	print "Starting Game...\n";
}

sub moveVal
{
    print ("BoxValue $BoxValue \n");
    $BoxValue = "X";
    print ("BoxValue $BoxValue \n");
}

sub newGame
{
    print "Pop-up with new game choice ... \n";
    $testext->destroy();
    createGrid();
}

sub finishGame
{
    print "Quitting Game...\n";
    exit(0);
}


