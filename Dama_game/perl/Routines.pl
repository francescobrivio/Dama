#!/usr/bin/perl

##### Functions #####
sub BEGIN
{
	#print "Starting Game...\n";
}

sub quit
{
    my $loc_pid = shift;
    #print "Quitting Game...\n";
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
    createGrid2();
    $d1->Show;
}

sub printFunc
{
    #print "$userEntry \n";
    print "$input \n";
}


sub beginGame
{
    $inner_team = shift;
    print WRITETO_C $inner_team;
    $d1->destroy();
    
    chomp ($newPositions = <READFROM_C>);
    @positions = split//,$newPositions;
    &loopOnButtons(\@positions);
}


1;

