#!/usr/bin/perl

sub createGrid2
{
    #my $counter;
    foreach $num (1 .. 8)
    {
        my $counter = 0;
        foreach $let ("a" .. "h")
        {
            my $position = $counter + (($num -1) * 8);
            push @buttons, $gridframe->Button(-text=>"$num$let", -relief=>'flat',
					      -image=>$dama_empty_scaled,
					      -command=>sub{
                                          my $testo_move = $user_move->cget(-textvariable);
                                          my $testo_bott = $buttons[$position]->cget(-text);
                                          if ($testo_move =~ /$testo_bott/g)
                                          {
                                            my $pos = pos($testo_move); # "pos" gives the position in the variable of the regex m//g
                                            $user_move->delete($pos-2,$pos);
                                          }
                                          else
                                          {
                                            $user_move->configure(-textvariable=>$testo_move.$testo_bott);
                                          }
                                          #&highlightMove($user_move->cget(-textvariable));
                                          &highlightMove($testo_bott);
                                        }
                                    );

            if ($num % 2 == 0)
            {
                if ($counter % 2 == 0) {$buttons[$position]->configure( -fg=>'sienna'  , -bg=>'sienna')  ;}
                else                   {$buttons[$position]->configure( -fg=>'moccasin', -bg=>'moccasin');}
            }
            else
            {
                if ($counter % 2 != 0) {$buttons[$position]->configure( -fg=>'sienna'  , -bg=>'sienna')  ;}
                else                   {$buttons[$position]->configure( -fg=>'moccasin', -bg=>'moccasin');}
            }
            $counter++;
        }
    }

    foreach $num2 (reverse 1 .. 8)
    {
        my $index = ($num2-1)*8;
        $gridframe->Button(-text=>"$num2", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black')->grid
        (
            $buttons[0+$index], $buttons[1+$index], $buttons[2+$index],
            $buttons[3+$index], $buttons[4+$index], $buttons[5+$index],
            $buttons[6+$index], $buttons[7+$index]
        );
    }
    
    $gridframe->Button(-text=>"  ", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black')->grid
    ($gridframe->Button(-text=>"a", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
     $gridframe->Button(-text=>"b", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
     $gridframe->Button(-text=>"c", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
     $gridframe->Button(-text=>"d", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
     $gridframe->Button(-text=>"e", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
     $gridframe->Button(-text=>"f", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
     $gridframe->Button(-text=>"g", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
     $gridframe->Button(-text=>"h", -relief=>'flat', -height=>'1', -width=>'1', -state=>'disabled', -disabledforeground=>'black'),
    );
    
}

sub loopOnButtons
{
    my @inner_positions = @{$_[0]};
    my $k = 0;
    &restoreColors();
    
    # Fill the board cell with the correct figure (pawn, pedone, empty)
    foreach (@buttons)
    {
        if      ($inner_positions[$k] eq "w") {$_->configure(-image=> $dama_bianca_scaled)  ;}
        elsif   ($inner_positions[$k] eq 'b') {$_->configure(-image=> $dama_nera_scaled)    ;}
        elsif   ($inner_positions[$k] eq 'W') {$_->configure(-image=> $damone_bianco_scaled);}
        elsif   ($inner_positions[$k] eq 'B') {$_->configure(-image=> $damone_nero_scaled)  ;}
        else                                  {$_->configure(-image=> $dama_empty_scaled)   ;}

        $k++;
    }
}

# Highlight the board cell when the user presses the button
sub highlightMove
{
  my $moveToColor = shift;
  my @moves_array = ( $moveToColor =~ m/../g );
  my $color = '';
  my $k = 0;
  foreach (@buttons)
  {
    foreach $move_array (@moves_array)
    {
      if ($_->cget(-text) eq $move_array)
      {
	  if ($_->cget(-bg) eq 'red')
	  {
	      $color = getColor($k);
	      $_->configure(-bg=>$color);
	  }
	  else {$_->configure(-bg=>'red');}
      }
    }
    $k++;
  }
}

# Restore the original colors of the board cells
sub restoreColors
{
  my $k = 0;
  my $color = '';

  foreach (@buttons)
  {
      #if ( ($k/8) % 2 == 0)
      #{
      #if ($k % 2 == 0) {$_->configure(-bg=>'sienna');}
      #else             {$_->configure(-bg=>'moccasin');}
      #}
      #else
      #{
      #if ($k % 2 == 1) {$_->configure(-bg=>'sienna');}
      #else             {$_->configure(-bg=>'moccasin');}
      #}
    $color = getColor($k);
    $_->configure(-bg=>$color);
    $k++;
  }
}

sub getColor
{
  my $k = shift;
  my $color = '';
  
  if ( ($k/8) % 2 == 0)
  {
    if ($k % 2 == 0) {$color = 'sienna';}
    else             {$color = 'moccasin';}
  }
  else
  {
    if ($k % 2 == 1) {$color = 'sienna';}
    else             {$color = 'moccasin';}
  }

  return $color;
}

1;

