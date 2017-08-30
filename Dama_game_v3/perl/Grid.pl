#!/usr/bin/perl

sub createGrid2
{
    my $counter;
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
                                            my $pos = pos($testo_move);
                                            $user_move->delete($pos-2,$pos);
                                          }
                                          else
                                          {
                                            $user_move->configure(-textvariable=>$testo_move.$testo_bott);
                                          }
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
    $k = 0;
    foreach (@buttons)
    {
        if      ($inner_positions[$k] eq "w") {$_->configure(-image=> $dama_bianca_scaled)  ;}
        elsif   ($inner_positions[$k] eq 'b') {$_->configure(-image=> $dama_nera_scaled)    ;}
        elsif   ($inner_positions[$k] eq 'W') {$_->configure(-image=> $damone_bianco_scaled);}
        elsif   ($inner_positions[$k] eq 'B') {$_->configure(-image=> $damone_nero_scaled)  ;}
        else                                  {$_->configure(-image=> $dama_empty_scaled); }

        $k++;
    }
}

1;

