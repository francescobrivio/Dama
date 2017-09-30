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
  system("kill $exe_pid");
  system("kill $cpp_pid");
  system("kill $tk_pid");
  exit(0);
}

#sub clear
#{
#    $gf = shift;
#    my @w = $gf->packSlaves;
#    foreach (@w) { $_->packForget; }
#}

sub newGame
{
  if ($d2){$d2->destroy();}
  if (@buttons[0] == 0){createGrid2();}
  else{
        print WRITETO_C "end\n";

	chomp(my $endGame = <READFROM_C>);
	chomp(my $endMatch = <READFROM_C>);
	chomp(my $winner = <READFROM_C>);
	chomp(my $move_fromC = <READFROM_C>);
	chomp(my $flag_msg = <READFROM_C>);
	chomp(my $error_msg = <READFROM_C>);
	chomp(my $newPositions = <READFROM_C>);

	$user_move->delete('0.0','end');
	$log->delete('0.0','end');	
	$log->insert('end', "----------- WELCOME TO DAMA -----------\n", 'green');
	$log->insert('end', " Select \"File->NewGame\" to begin and\n");
	$log->insert('end', " remember, WHITE always starts first.\n");
	$log->insert('end', "---------------------------------------\n", 'green');
    }
    
     # Dialog for game mode decision    
    $d0 = $mw->Dialog(-text=>"Choose the game mode!", -popover=>$gridframe, -buttons=>[]);
    my $PvsP = $d0->Radiobutton(-text=>'Player vs Player', -value=>0, -variable=>\$CPU, -command=>[\&gameMode, 0]);
    $PvsP->pack();
    my $PvsC = $d0->Radiobutton(-text=>'Player vs CPU', -value=>1, -variable=>\$CPU, -command=>[\&gameMode, 1]);
    $PvsC->pack();

    $d0->Show;
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

    # Dialog for team color decision                                                                                                                              
    $d1 = $mw->Dialog(-text=>"Choose the color of you team!", -popover=>$gridframe, -buttons=>[]);
    my $black_team = $d1->Radiobutton(-text=>'black', -value=>'black', -variable=>\$team, 
				      -image=> $dama_nera_scaled  , -command=>[\&beginGame,"black\n",$CPU]);
    $black_team->pack();
    my $white_team = $d1->Radiobutton(-text=>'white', -value=>'white', -variable=>\$team, 
				      -image=> $dama_bianca_scaled, -command=>[\&beginGame,"white\n",$CPU]);
    $white_team->pack();

    $d1->Show;
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

    chomp(my $newPositions = <READFROM_C>);
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


sub countPawns
{
    my @inner_positions = @{$_[0]};
    
    my $nwhite = 0;
    my $nblack = 0;
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
    if($d3){$d3->destroy();}

    my $move = shift;

    print WRITETO_C $move;

    chomp(my $endGame = <READFROM_C>);
    chomp(my $endMatch = <READFROM_C>);
    chomp(my $winner = <READFROM_C>);
    chomp(my $move_fromC = <READFROM_C>);
    chomp(my $flag_msg = <READFROM_C>);
    chomp(my $error_msg = <READFROM_C>);
    chomp(my $newPositions = <READFROM_C>);

    my @flag_split = split //, $flag_msg;

    &loggingMove($flag_msg, $move_fromC, $error_msg);
      
    my @positions = split//, $newPositions;
    &loopOnButtons(\@positions);
    &countPawns(\@positions);
    $user_move->delete(0,30);
    
     if($endMatch == 1)
     {
	 #print "END GAME\n";
	 $log->insert('end',"---------- GAME FINISHED!! ----------\n", 'red');
	 if($winner eq 'draw')
	 {$log->insert('end',"The game is drawn!!\n");}
	 else
	 {$log->insert('end',"The $winner win!!\n");}
	 $log->see('end');

	 $CPUgoON = 0;
	 my $playVar = 0;
	 $d2 = $mw->Dialog(-text=>"Do you want play again?", -popover=>$gridframe, -buttons=>[]);
	 my $play_buttom = $d2->Radiobutton(-text=>'Play again', -value=> 1, -variable=>\$playVar,
					    -command=>[\&newGame]);
	 $play_buttom->pack();
	 my $quit_buttom = $d2->Radiobutton(-text=>'Quit', -value=> 0, -variable=>\$playVar,
					    -command=>[\&quit,$$,$pid,$pid_cpp]);
	 $quit_buttom->pack();
	 $d2->Show;
     }
    else
    {
	# If flag is 0 (i.e. not a good move), tell PC to wait
	if   (@flag_split[0] == 1) {$CPUgoON = 1;}
	else                       {$CPUgoON = 0;}
    }
}


sub loggingMove
{
  my $flag_msg = shift;
  my $move_fromC = shift;
  my $error_log = shift;

  my @flag_split = split //, $flag_msg;
  my @log_move   = split //, $move_fromC;

  my $npawns = 0;
  my $player = ' ';

  if ($flag_split[0] == 1)
  {
    if($flag_split[1] eq 'w' || $flag_split[1] eq 'W')
      {$player = 'White';}
    elsif ($flag_split[1] eq 'b' || $flag_split[1] eq 'B')
      {$player = 'Black';}
    elsif ($flag_split[1] eq 'a')
      {$player = 'PC';}
    else
    {
      $log->insert('end', " WTF is going on?!?! who is playing?!?! \n Machines are taking over...", 'red');
      $log->see('end');
    }
    
    if($player ne ' ')
    {
	if(abs($log_move[2]-$log_move[0]) == 1)
	{$log->insert('end', "$player moves: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");}
	else
	{
	    $npawns = abs($log_move[2]-$log_move[0])/2;
	    $log->insert('end', "$player eats $npawns pawns: $log_move[0]$log_move[1] --> $log_move[2]$log_move[3] \n");
	}
	$log->see('end');
    }
  }
  else
  {
    $log->insert('end', "Move not allowed! \n", 'red');
    $log->insert('end', "ERROR: ", 'red');
    $log->insert('end', "$error_log \n", 'white');
    $log->insert('end', "Try again! \n", 'green');
    $log->see('end');
  }

}

sub showHelpPanel
{
  $helpText = <<END_MESSAGE;
-- MAIN INSTRUCTIONS --
1. Wins whoever eats all the opponent's pawns or if the opponent can't move anymore
2. Pawns move only forward and diagonally
3. You can eat an opponent pawn by "jumping" over it, multiple "jump" are allowed
4. Big pawns can also move backwards
5. Pawns can not eat big pawns
6. White team always moves first

-- HOW TO PLAY --
1. Click on a pawn to select it
2. Click on the cell where you want to move the selected pawn
3. If you want to make a multiple "jump", select all the intermediate cells
4. Once you chose your move, click "Enter Move" to play your move
5. If you want to change your move, click "Clear Move" or click again on the cell
END_MESSAGE

  $helpPanel = $mw->Scrolled("Dialog", -scrollbars => 'e', -title=>'Help message', -text=>$helpText, -width=>40);
  $helpPanel->Show;
}


sub GiveUpConfirm
{
    #Dialog for give up decision                                                                                 
    my $quit_var;
    $d3 = $mw->Dialog(-text=>"Do you really want to give up?", -popover=>$gridframe, -buttons=>[]);
    my $yes_buttom = $d3->Radiobutton(-text=>'Yes', -value=>1, -variable=>\$quit_var, -command=>[\&doTheMove, "none\n"]);
    $yes_buttom->pack();
    my $no_buttom = $d3->Radiobutton(-text=>'No', -value=>0, -variable=>\$quit_var, -command=>[\&Resume]);
    $no_buttom->pack();
    
    $d3->Show;
}

sub QuitConfirm
{
    #Dialog for quit decision  
    my $quit_var;
    $d4 = $mw->Dialog(-text=>"Do you really want to quit?", -popover=>$gridframe, -buttons=>[]);
    my $yes_buttom = $d4->Radiobutton(-text=>'Yes', -value=>1, -variable=>\$quit_var, -command=>[\&quit,$$,$pid,$pid_cpp]);
    $yes_buttom->pack();
    my $no_buttom = $d4->Radiobutton(-text=>'No', -value=>0, -variable=>\$quit_var, -command=>[\&Resume]);
    $no_buttom->pack();

    $d4->Show; 
}

sub Resume
{
    if($d3){$d3->destroy();}
    if($d4){$d4->destroy();}
}

1;

