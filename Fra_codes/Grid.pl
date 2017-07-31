#!/usr/bin/perl

sub createGrid
{
    $gridframe->Button(-text=>"8", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_8a = $gridframe->Button(-text=>"8a", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'), #, -command=>sub{print $cell_8a->cget(-text)}),
         $cell_8b = $gridframe->Button(-text=>"8b", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'), #, -image=>$img_dama_bianca
         $cell_8c = $gridframe->Button(-text=>"8c", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2', -command=>[\&whoami, $self]),
         $cell_8d = $gridframe->Button(-text=>"8d", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_8e = $gridframe->Button(-text=>"8e", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_8f = $gridframe->Button(-text=>"8f", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_8g = $gridframe->Button(-text=>"8g", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_8h = $gridframe->Button(-text=>"8h", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"7", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_7a = $gridframe->Button(-text=>"7a", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_7b = $gridframe->Button(-text=>"7b", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_7c = $gridframe->Button(-text=>"7c", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_7d = $gridframe->Button(-text=>"7d", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_7e = $gridframe->Button(-text=>"7e", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_7f = $gridframe->Button(-text=>"7f", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_7g = $gridframe->Button(-text=>"7g", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_7h = $gridframe->Button(-text=>"7h", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"6", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_6a = $gridframe->Button(-text=>"6a", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_6b = $gridframe->Button(-text=>"6b", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_6c = $gridframe->Button(-text=>"6c", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_6d = $gridframe->Button(-text=>"6d", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_6e = $gridframe->Button(-text=>"6e", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_6f = $gridframe->Button(-text=>"6f", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_6g = $gridframe->Button(-text=>"6g", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_6h = $gridframe->Button(-text=>"6h", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"5", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_5a = $gridframe->Button(-text=>"5a", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_5b = $gridframe->Button(-text=>"5b", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_5c = $gridframe->Button(-text=>"5c", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_5d = $gridframe->Button(-text=>"5d", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_5e = $gridframe->Button(-text=>"5e", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_5f = $gridframe->Button(-text=>"5f", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_5g = $gridframe->Button(-text=>"5g", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_5h = $gridframe->Button(-text=>"5h", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"4", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_4a = $gridframe->Button(-text=>"4a", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_4b = $gridframe->Button(-text=>"4b", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_4c = $gridframe->Button(-text=>"4c", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_4d = $gridframe->Button(-text=>"4d", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_4e = $gridframe->Button(-text=>"4e", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_4f = $gridframe->Button(-text=>"4f", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_4g = $gridframe->Button(-text=>"4g", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_4h = $gridframe->Button(-text=>"4h", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"3", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_3a = $gridframe->Button(-text=>"3a", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_3b = $gridframe->Button(-text=>"3b", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_3c = $gridframe->Button(-text=>"3c", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_3d = $gridframe->Button(-text=>"3d", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_3e = $gridframe->Button(-text=>"3e", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_3f = $gridframe->Button(-text=>"3f", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_3g = $gridframe->Button(-text=>"3g", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_3h = $gridframe->Button(-text=>"3h", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"2", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_2a = $gridframe->Button(-text=>"2a", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_2b = $gridframe->Button(-text=>"2b", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_2c = $gridframe->Button(-text=>"2c", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_2d = $gridframe->Button(-text=>"2d", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_2e = $gridframe->Button(-text=>"2e", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_2f = $gridframe->Button(-text=>"2f", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_2g = $gridframe->Button(-text=>"2g", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_2h = $gridframe->Button(-text=>"2h", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"1", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($cell_1a = $gridframe->Button(-text=>"1a", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_1b = $gridframe->Button(-text=>"1b", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_1c = $gridframe->Button(-text=>"1c", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_1d = $gridframe->Button(-text=>"1d", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_1e = $gridframe->Button(-text=>"1e", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_1f = $gridframe->Button(-text=>"1f", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
         $cell_1g = $gridframe->Button(-text=>"1g", -relief=>'flat', -fg=>'sienna', -bg=>'sienna',     -width=>'2', -height=>'2'),
         $cell_1h = $gridframe->Button(-text=>"1h", -relief=>'flat', -fg=>'moccasin', -bg=>'moccasin', -width=>'2', -height=>'2'),
        );

    $gridframe->Button(-text=>"  ", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2')->grid
        ($gridframe->Button(-text=>"a", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
         $gridframe->Button(-text=>"b", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
         $gridframe->Button(-text=>"c", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
         $gridframe->Button(-text=>"d", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
         $gridframe->Button(-text=>"e", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
         $gridframe->Button(-text=>"f", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
         $gridframe->Button(-text=>"g", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
         $gridframe->Button(-text=>"h", -relief=>'flat', -bg=>'white', -width=>'2', -height=>'2'),
        );
    
    #%buttonsToNames = reverse %namesToButtons;
    #@buttonsList = ($cell_8a, $cell_8b,$cell_8c,$cell_8d,$cell_8e,$cell_8f,$cell_8g,$cell_8h);#,
#    $cell_a, $cell_b,$cell_c,$cell_d,$cell_e,$cell_f,$cell_g,$cell_h,
#    $cell_a, $cell_b,$cell_c,$cell_d,$cell_e,$cell_f,$cell_g,$cell_h,
#    $cell_a, $cell_b,$cell_c,$cell_d,$cell_e,$cell_f,$cell_g,$cell_h,
#    $cell_a, $cell_b,$cell_c,$cell_d,$cell_e,$cell_f,$cell_g,$cell_h,
#    $cell_a, $cell_b,$cell_c,$cell_d,$cell_e,$cell_f,$cell_g,$cell_h,
#    $cell_a, $cell_b,$cell_c,$cell_d,$cell_e,$cell_f,$cell_g,$cell_h,
#    $cell_a, $cell_b,$cell_c,$cell_d,$cell_e,$cell_f,$cell_g,$cell_h);
    #foreach (@buttonsList)
    #{
    #    $_->configure(-command=>sub{print $_->cget(-text)})
    #}
    #foreach $key (keys %namesToButtons)
    #{
        #print "key: " . $key . " value:" . $buttonsToNames[$key] . "\n";
        #unshift(@buttonsList, $key);
        #$key->configure(-command=>[\&whoami,$key]);
    #}
}

sub configureGrid
{
    @buttonsList = ($cell_8a, $cell_8b,$cell_8c,$cell_8d,$cell_8e,$cell_8f,$cell_8g,$cell_8h);
    foreach (@buttonsList)
    {
        print "cell: $_ \n";
        $val = $_->cget(-text);
        print "val $val \n";
        $_->configure(-command=>sub{print $val});
    }

}

%namesToButtons = (
    '8a' => $cell_8a,
    '8b' => $cell_8b,
    '8c' => $cell_8c,
    '8d' => $cell_8d,
    '8e' => $cell_8e,
    '8f' => $cell_8f,
    '8g' => $cell_8g,
    '8h' => $cell_8h,

    '7a' => $cell_7a,
    '7b' => $cell_7b,
    '7c' => $cell_7c,
    '7d' => $cell_7d,
    '7e' => $cell_7e,
    '7f' => $cell_7f,
    '7g' => $cell_7g,
    '7h' => $cell_7h,

    '6a' => $cell_6a,
    '6b' => $cell_6b,
    '6c' => $cell_6c,
    '6d' => $cell_6d,
    '6e' => $cell_6e,
    '6f' => $cell_6f,
    '6g' => $cell_6g,
    '6h' => $cell_6h,

    '5a' => $cell_5a,
    '5b' => $cell_5b,
    '5c' => $cell_5c,
    '5d' => $cell_5d,
    '5e' => $cell_5e,
    '5f' => $cell_5f,
    '5g' => $cell_5g,
    '5h' => $cell_5h,

    '4a' => $cell_4a,
    '4b' => $cell_4b,
    '4c' => $cell_4c,
    '4d' => $cell_4d,
    '4e' => $cell_4e,
    '4f' => $cell_4f,
    '4g' => $cell_4g,
    '4h' => $cell_4h,

    '3a' => $cell_3a,
    '3b' => $cell_3b,
    '3c' => $cell_3c,
    '3d' => $cell_3d,
    '3e' => $cell_3e,
    '3f' => $cell_3f,
    '3g' => $cell_3g,
    '3h' => $cell_3h,

    '2a' => $cell_2a,
    '2b' => $cell_2b,
    '2c' => $cell_2c,
    '2d' => $cell_2d,
    '2e' => $cell_2e,
    '2f' => $cell_2f,
    '2g' => $cell_2g,
    '2h' => $cell_2h,

    '1a' => $cell_1a,
    '1b' => $cell_1b,
    '1c' => $cell_1c,
    '1d' => $cell_1d,
    '1e' => $cell_1e,
    '1f' => $cell_1f,
    '1g' => $cell_1g,
    '1h' => $cell_1h,
);





1;

