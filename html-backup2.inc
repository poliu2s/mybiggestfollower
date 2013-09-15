<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <title>My Biggest Follower</title>
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.1/jquery.min.js">
    </script>
    <link href="../bootstrap/css/bootstrap.css" rel="stylesheet">
    <style type="text/css">
      /*img {border-width: 0}
      * {font-family:'Lucida Grande', sans-serif;}
      
      text {
        font: 10px sans-serif;
      }*/



      body {
        padding-top: 20px;
        padding-bottom: 40px;
      }

      /* Custom container */
      .container-narrow {
        margin: 0 auto;
        max-width: 700px;
      }
      .container-narrow > hr {
        margin: 30px 0;
      }

      /* Main marketing message and sign up button */
      .jumbotron {
        margin: 60px 0;
        text-align: center;
      }
      .jumbotron h1 {
        font-size: 72px;
        line-height: 1;
      }
      .jumbotron .btn {
        font-size: 21px;
        padding: 14px 24px;
      }

      /* Supporting marketing content */
      .marketing {
        margin: 60px 0;
      }
      .marketing p + h4 {
        margin-top: 28px;
      }
    </style>
    <link href="../assets/css/bootstrap-responsive.css" rel="stylesheet">

    <!-- HTML5 shim, for IE6-8 support of HTML5 elements -->
    <!--[if lt IE 9]>
      <script src="../assets/js/html5shiv.js"></script>
    <![endif]-->

    <!-- Fav and touch icons -->
    <link rel="apple-touch-icon-precomposed" sizes="144x144" href="../assets/ico/apple-touch-icon-144-precomposed.png">
    <link rel="apple-touch-icon-precomposed" sizes="114x114" href="../assets/ico/apple-touch-icon-114-precomposed.png">
      <link rel="apple-touch-icon-precomposed" sizes="72x72" href="../assets/ico/apple-touch-icon-72-precomposed.png">
                    <link rel="apple-touch-icon-precomposed" href="../assets/ico/apple-touch-icon-57-precomposed.png">
                                   <link rel="shortcut icon" href="../assets/ico/favicon.png">
  </head>
  <body>
    <script src="http://d3js.org/d3.v3.min.js"></script>
    <div class="container-narrow">

      <div class="masthead">
        <ul class="nav nav-pills pull-right">
          <li class="active"><a href="#">Home</a></li>
          <li><a href="mailto:po.liu.2s@gmail.com">Contact</a></li>
        </ul>
        <h3><a href="http://ca.linkedin.com/in/poliu2s/">Po Liu</a></h3>
      </div>

      <hr>

      <div class="jumbotron">
        <h2>My Biggest</h2>
        <img src="flask.jpg" />
        <h1>Follower</h1>
        <p class="lead">A webapp designed to visualize the magnitude of influence for each of your followers. If you are having issues try <a href='./clearsessions.php'>clearing your session</a>.</p>
        <?php print_r($sign_in_button); ?>
      </div>

      <hr>

      <div class="row-fluid marketing" style="margin: 0px">
        <?php

        if ($sign_in == 0) {
          // Create a connection with the database
          $host = "127.12.191.130";
          $username="admin7I4NNiI";
          $password="Z6Yt_GAZkX_Q";
          $db_name="mybiggestfollower";
          $db = new mysqli("$host", "$username", "$password", "$db_name") or die("Database could not connect");

          // Set up database credentials
          $user_query = "SELECT *
                         FROM bubbles
                         WHERE owner='".$screen_name."'";
          $user_response = $db->query($user_query);
          $entry = $user_response->fetch_assoc();
          
          // For debugging
          var_dump($entry);
          
          // Check if user already exists in database - do not waste Twitter API calls
          if (is_null($entry)) {
            echo "entered here";
            $cursor = -1;
            do {
              // Add user's follower information to the database
              $response = $connection->get('followers/list', array("cursor" => (string)$cursor));

              // Update the cursor if more than 20 followers
              $cursor = $response->next_cursor;

              for($i = 0; $i < count($response->users); $i++) {
                // Store into db
                $insert_query = "INSERT INTO bubbles (screen_name, followers, owner)
                                 VALUES (\"".$response->users[$i]->screen_name."\", \"".$response->users[$i]->followers_count."\", \"".$screen_name."\")";
                $insert_response = $db->query($insert_query);
                //var_dump($insert_response);
              }
            } while ($cursor != 0);
            header('Location: ./index.php');
          }
      

          // Update JSON data file
          $file = "flare1.json"; 
          $handle = fopen($file, 'w');
          $json = '{ "name": "analytics","children": [ ';
          
          // Retrieve data from db
          for($i = 0; $i < $user_response->num_rows; $i++) {            
            // Write entry to JSON file
            $json = $json.'{ "name": "'.$i.'", "children": [ { "name" : "'.$entry['screen_name'].'", "size": '.$entry['followers'].'}]}';
            
            // Formating everything but the last entry
            if($i < $user_response->num_rows - 1) {
                $json = $json.',';
            }

            // Grab the entry from Twitter server's response
            $entry = $user_response->fetch_assoc();
          }
          
          $json = $json.']}';  // closing braces in json
          fwrite($Handle, $Data); 
          fwrite($handle, $json); 
          fclose($handle);

          // Display the bubble graph
          echo "<h3>".$user_response->num_rows." follower bubbles for user <i>".$screen_name."</i> : </h3>";
          echo '<iframe src="graph1.html" width=100% height=700px scrolling="no" style="height: auto" seamless/></iframe>';   
          echo '<hr>';
        }
        ?>
      
      
      <div class="footer">
        <p>2013 &copy; PoMart Inc. Built using PHP/D3 with OAuth for Twitter's REST API v1.1 by Abraham Williams.</p>
      </div>

    </div> <!-- /container -->
    

     <!-- Le javascript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="../assets/js/jquery.js"></script>
    <script src="../assets/js/bootstrap-transition.js"></script>
    <script src="../assets/js/bootstrap-alert.js"></script>
    <script src="../assets/js/bootstrap-modal.js"></script>
    <script src="../assets/js/bootstrap-dropdown.js"></script>
    <script src="../assets/js/bootstrap-scrollspy.js"></script>
    <script src="../assets/js/bootstrap-tab.js"></script>
    <script src="../assets/js/bootstrap-tooltip.js"></script>
    <script src="../assets/js/bootstrap-popover.js"></script>
    <script src="../assets/js/bootstrap-button.js"></script>
    <script src="../assets/js/bootstrap-collapse.js"></script>
    <script src="../assets/js/bootstrap-carousel.js"></script>
    <script src="../assets/js/bootstrap-typeahead.js"></script>

  </body>
</html>
