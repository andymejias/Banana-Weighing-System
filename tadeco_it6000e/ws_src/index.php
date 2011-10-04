<?php


include("iplist.php");
include("settings.php");
include("classes/service.class.inc");

$service = new RestService();
$service->handle();
