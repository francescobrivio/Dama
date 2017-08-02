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

sub clear
{
    $gf = shift;
    my @w = $gf->packSlaves;
    foreach (@w) { $_->packForget; }
}

sub newGame
{
    #$testext->destroy();
    createGrid2();
    #configureGrid();
    #$d1->Show;
}

sub printFunc
{
    #print "$userEntry \n";
    print "$input \n";
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

