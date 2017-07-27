#!/usr/bin/perl

use Tk;

my $mw = MainWindow->new;
$mw->geometry("250x140");
$mw->title ("A first Tk Demo");
$mw->Label(
            -text => "Some text"
          )->pack;
$mw->Button(
            -text    => "Print a Value",
            -command => \&printText
           )->pack;
$mw->Button(
            -text    => "Double the Value",
            -command => sub {$val *= 2}
           )->pack;
$mw->Button(
            -text    => "Quit",
            -command => \&finish
           )->pack;

MainLoop;


sub printText
{
    print "Value is $val\n";
}


sub finish
{
    print "Quitting...\n";
    print "Final Value is $val\n";
    exit(0);
}

sub BEGIN
{
	$val = 2;
	print "Initializing val to $val\n";
}

