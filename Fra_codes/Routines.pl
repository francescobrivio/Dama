#!/usr/bin/perl

sub newGame
{
    print "Pop-up with new game choice ... \n";
    $testext->destroy();
    createGrid();
    configureGrid();
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

sub whoami
{
    $cell = $_;
    print $cell->cget(-text);
}

sub black_move
{
    $cell_8b->configure(-text=>"O",
                        -fg=>"black",
                        -font=>"{bold}");
}

1;

