#!/usr/bin/perl

##### Functions #####
sub BEGIN
{
	#print "Starting Game...\n";
}

sub quit
{
    my $tk_pid = shift;
    my $cpp_pid = shift;
    my $exe_pid = shift;
    #print "Quitting Game...\n";
    system("kill $exe_pid");
    system("kill $cpp_pid");
    system("kill $tk_pid");
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
    $d0->Show;
}

sub printFunc
{
    #print "$userEntry \n";
    print "$input \n";
}


sub beginGame
{
    my $inner_team = shift;
    print WRITETO_C $inner_team;
    $d1->destroy();
    
    chomp ($newPositions = <READFROM_C>);
    @positions = split//,$newPositions;
    &loopOnButtons(\@positions);
}

sub gameMode
{
    my $cpu = shift;
    if($cpu == 0) {
	print "Mode: Player vs Player! \n"; }
    elsif($cpu == 1) {
	print "Mode: Player vs CPU! \n"; }
    else {
	print "Undefined mode! \n"; }

    $d0->destroy();
    $d1->Show;
    
}

1;

