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
    my $isCPU = shift;

    $log->insert('end', " Team chosen: $inner_team");
    $log->insert('end', "------------- GOOD LUCK! -------------\n", 'green');
    $log->insert('end', " MOVES LOG:\n", 'under');

    print WRITETO_C $inner_team;
    $d0->destroy();
    $d1->destroy();
    
    chomp($newPositions = <READFROM_C>);
    @positions = split//, $newPositions;            
    &loopOnButtons(\@positions);
    &countPawns(\@positions);
    $mw->update;
    chomp($inner_team);
    if (($inner_team eq 'black') and ($isCPU))
      {
        sleep(1);
        &doTheMove("auto\n");
      }
}

sub gameMode
{
    $cpu = shift;
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

sub doTheMove
{
    my $move = shift;
    
    print WRITETO_C $move;
    
    chomp($pos_fromC = <READFROM_C>);
    chomp($flag_msg = <READFROM_C>);
    
    @flag_split = split //, $flag_msg;
    if ($flag_split[0] == 1)
    {
      @log_move = split //, $pos_fromC;

      if ($flag_split[1] eq 'w' || $flag_split[1] eq 'W')
      {
        $log->insert('end', " White: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
        $log->see('end');
      }
      elsif ($flag_split[1] eq 'b' || $flag_split[1] eq 'B')
      {
        $log->insert('end', " Black: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
        $log->see('end');
      }
      else
      {
        $log->insert('end', " PC   : $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
        $log->see('end');
      }
    }
    else
    {
      $log->insert('end', " Move not allowed!Try again!\n", 'red');
      $log->see('end');
    }

    chomp($newPositions = <READFROM_C>);
    @positions = split//, $newPositions;            
    &loopOnButtons(\@positions);
    &countPawns(\@positions);
    chomp($endGame = <READFROM_C>);
    $user_move->delete(0,30);

    if($endGame == 1)
    {
      print "END GAME\n";
      $log->insert('end',"---------- GAME FINISHED!! ----------\n", 'red');
      $log->insert('end'," who's the winner??\n");
      $log->see('end');
    }

}


1;

