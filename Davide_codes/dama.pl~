#!/usr/bin/perl

use IPC::Open2;

my $pid = open2(*Reader, *Writer, "./dama.exe") or die "$!";

$question = <Reader>;
print Writer("A3B4\n");
print("mossa: A3B4 \n");
$answer = <Reader>;
print("$answer \n");
sleep(1);

print ("end!");
close(Writer);
close(Reader);
