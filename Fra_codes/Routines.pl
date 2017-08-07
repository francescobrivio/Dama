#!/usr/bin/perl

##### Functions #####
sub BEGIN
{
	print "Starting Game...\n";
}

sub quit
{
    my $loc_pid = shift;
    print "Quitting Game...\n";
    system("kill $loc_pid");
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
    $testext->destroy();
    createGrid2();
    #$d1->Show;
}

sub printFunc
{
    #print "$userEntry \n";
    print "$input \n";
}


sub black_move
{
    $cell_8b->configure(-text=>"O",
                        -fg=>"black",
                        -font=>"{bold}");
}


sub changeImage
{
    my($widget) = @_;
    chomp(my $newPosition = <$READFROM_CPP>);
    $widget->configure(-command=>sub{
                                    print "prima: @newPositions \n";
                                    @fake_positions = split//,$newPositions;
                                    print "tasto: ".$newPositions."\n";
                                    &loopOnButtons(\@fake_positions)
                                    }
                      );

}

1;

