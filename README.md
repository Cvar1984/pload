# Pload
PHP LD_PRELOAD Payload. A tool to bypass __disable_functions__.

## How it works

PHP in Linux calls a binary (sendmail) when the mail() function is executed. If we have putenv() allowed, we can set the environment variable "LD_PRELOAD", so we can preload an arbitrary shared object. Our shared object will execute our custom payload (a binary or a bash script) without the PHP restrictions, so we can have a reverse shell, for example.
## how to do it
1. compile your shared object, move it to where you want e.g /tmp/preload.so
2. compile your own arbitrary C code or you can use bash script and then move it e.g /tmp/payload
3. execute exploit.php and enjoy
