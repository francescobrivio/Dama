#!/usr/bin/perl

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

sub newGame
{
    use 5.010;
    $testext->destroy();
    createGrid();
    #$d1->Show;
}

sub printFunc
{
    print "$userEntry \n";
}

sub white_move
{
    $cell_8a->configure(-text=>"O",
                        -fg=>"white",
                        -font=>"{bold}");
}

sub black_move
{
    $cell_8b->configure(-text=>"O",
                        -fg=>"black",
                        -font=>"{bold}");
}

1;

