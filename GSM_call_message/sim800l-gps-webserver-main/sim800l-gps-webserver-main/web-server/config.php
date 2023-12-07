<?php 
$dbServername ="localhost";
$dbUsername="root";
$dbPassword="";
$dbName="ajspdb";

date_default_timezone_set('Asia/Colombo');

// Connect with the database 
$conn=mysqli_connect($dbServername,$dbUsername,$dbPassword,$dbName);
 
// Display error if failed to connect 
if (!$conn) { 
    die( "Connection to database is failed: ".mysqli_connect_error());
}

?>