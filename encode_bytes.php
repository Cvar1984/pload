<?php

function file_to_byte_array($filename) {
$contents = file_get_contents($filename, true);
$bytes = unpack("C*", $contents);
return $bytes;
}

$b = file_to_byte_array($argv[1]);

echo implode(",",$b);

