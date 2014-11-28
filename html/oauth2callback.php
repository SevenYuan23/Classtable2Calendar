<?php
	require_once"../google-api-php-client/autoload.php";

	session_start();

	$client=new Google_Client();
	$client->setAuthConfigFile('/home/sevenyuan/client_secret.json');
	$client->setRedirectUri("http://classtable.com/oauth2callback.php");
	$client->addScope('https://www.googleapis.com/auth/calendar');

	if(! isset($_GET['code'])){
		$auth_url=$client->createAuthUrl();
		header('Location:'.filter_var($auth_url,FILTER_SANITIZE_URL));
	}else{
		$client->authenticate($_GET['code']);
		$_SESSION['access_token']=$client->getAccessToken();
		$redirect_uri="http://classtable.com/";
		header('Location:'.filter_var($redirect_uri,FILTER_SANITIZE_URL));
	}
?>
