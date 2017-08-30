#!/usr/bin/perl

##### Functions #####
sub BEGIN
{
	print "Starting Game...\n";
}

sub quit
{
    print "Quitting Game...\n";
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
    $log->insert('end', " Team chosen: $inner_team");
    $log->insert('end', "------------- GOOD LUCK! -------------\n", 'green');
    $log->insert('end', " MOVES LOG:\n", 'under');

    print WRITETO_C $inner_team;
    $d1->destroy();
    
    chomp ($newPositions = <READFROM_C>);
    @positions = split//,$newPositions;
    &loopOnButtons(\@positions);
    &countPawns(\@positions);
}

sub gameMode
{
    my $cpu = shift;
    if($cpu == 0)
      {
        $log->insert('end', " Game mode chosen: Player vs Player\n");
      }
    elsif($cpu == 1)
      {
        $log->insert('end', " Game mode chosen: Player vs CPU\n");
      }
    else
      {
        $log->insert('end', " Undefined mode, please try again!\n");
      }

    $d0->destroy();
    $d1->Show;
    
}

sub countPawns
{
    my @inner_positions = @{$_[0]};
    
    $nwhite = 0;
    $nblack = 0;
    foreach (@inner_positions)
    {
        if ($_ eq 'w' || $_ eq 'W') {$nwhite = $nwhite + 1;}
        if ($_ eq 'b' || $_ eq 'B') {$nblack = $nblack + 1;}
    }
    
    $nWhite_entry->configure(-textvariable=>$nwhite);
    $nBlack_entry->configure(-textvariable=>$nblack);
    
}

1;

