#!/usr/bin/perl

use Tk;


my $mw = MainWindow->new;
$mw->geometry("600x400");
$mw->title ("Test Dama");

$menubar = $mw->Frame();
$filemenu = $menubar->Menubutton(-text => 'File');

my $topframe = $mw->Frame(-bg=>'yellow')->grid( -row => 2, -column => 0 );
$topframe->Button( -text => "But 0 0")->grid( -row => 0, -column => 0 );
$topframe->Button( -text => "But 1 1")->grid( -row => 1, -column => 1 );

my $other = $topframe->Frame(-bg=>'red')->grid( -row => 2, -column => 0 );
$other->Button( -text => "Oth 0 0")->grid( -row => 0, -column => 0 );
$other->Button( -text => "Oth 1 1")->grid( -row => 1, -column => 1 );
$other->Button( -text => "Oth 2 0")->grid( -row => 2, -column => 1 );



# a Frame you'll never see
#$frame1 = $mw->Frame;
#$frame1->Button(-text => 'button1')->pack;
#$frame1->Button(-text => 'button2')->pack;

# a more visible Frame
#$frame2 = $mw->Frame(-borderwidth => 2, -relief => 'groove');
#$frame2->Button(-text => 'button1, frame2')->pack;
#$frame2->Button(-text => 'button2, frame2')->pack;

# a Frame in a Frame
#$frame3 = $frame2->Frame(-borderwidth => 3, -relief => 'raised');
#$frame3->Button(-text => 'button1, frame3')->pack;

#$frame3->pack;  # not visible yet
#$frame2->pack;  # still nothing visible...
#$menubar->pack(-side=>"top", -fill=>"x");
#$frame1->pack;  # now we can see all the Frames and Buttons


$mw->MainLoop;


