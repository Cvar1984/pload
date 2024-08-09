# Pload
PHP LD_PRELOAD Payload. A tool to bypass __disable_functions__.

## How it works

PHP in Linux calls a binary (sendmail) when the mail() function is executed. If we have putenv() allowed, we can set the environment variable "LD_PRELOAD", so we can preload an arbitrary shared object. Our shared object will execute our custom payload (a binary or a bash script) without the PHP restrictions, so we can have a reverse shell, for example.
## how to do it
run exploit.php and connect using gsocket client
