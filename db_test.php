<?php
	$host = "127.12.191.130";
	$username="admin7I4NNiI";
	$password="Z6Yt_GAZkX_Q";
	$db_name="mybiggestfollower";

	$db = new mysqli("$host", "$username", "$password", "$db_name") or die("Database could not connect");
	$query = "SELECT *
	        FROM bubbles
	        WHERE owner='poliu2s'";
	$result = $db->query($query);

	var_dump($result->fetch_assoc());

	$insert_query = "INSERT INTO bubbles (screen_name, followers, owner)
                     VALUES ( po_rpi, 20, poliu3s)";
    $db->query($insert_query->fetch_assoc();
?>