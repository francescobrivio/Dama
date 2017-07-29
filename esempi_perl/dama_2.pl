#!/usr/bin/perl

##### Packages #####
use Tk;

##### Main #####
my $mw = MainWindow->new;
$mw->geometry("700x400");
$mw->title ("Test Dama");

$menuframe = $mw->Frame(-bd=>2, -relief=>'raised');
$menuframe->pack(-side=>"top", -fill=>"x");

    $filemenu = $menuframe->Menubutton(-text=>'File');
    $filemenu->pack(-side=>"left", -fill=>"x");

    $quitmenu = $menuframe->Button( -text=>"Quit", -command=>\&finishGame)->pack;
    $quitmenu->pack(-side=>"right");

$logframe = $mw->LabFrame(-label=>"Moves Log", -bd=>2, -relief=>'raised', -width=>"50");
$logframe->pack(-side=>"right", -fill=>"both");

    $log = $logframe->Button(-text=>'qui il log vero');
    $log->pack(-side=>"top");

$gridframe = $mw->LabFrame(-label=>"Dama", -bd=>2, -relief=>'raised');
$gridframe->pack(-side=>"left", -fill=>"both", -expand=>1, -pady=>'0');

    $testext = $gridframe->Button(-text=>"griglia qui");
    $testext->pack();


##### Loop #####
$mw->MainLoop;

##### Functions #####
sub BEGIN
{
	print "Starting Game...\n";
}

sub finishGame
{
    print "Quitting Game...\n";
    exit(0);
}


