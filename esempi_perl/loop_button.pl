#!/usr/bin/perl

use Tk;
use strict;

my $mw =  MainWindow->new;
$mw->geometry("700x500");

my @buttons;

for my $i (0 .. 2)
{
    push @buttons, $mw->Button(-text => "bott $i",
                                -command => sub{
                                                print $buttons[$i]->cget(-text),"\n";
                                                }
                               )->pack;
}

MainLoop();

