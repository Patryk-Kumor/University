<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
    </head>
    <body>
        <form action="action_page.php" method="post">
        name:<br>
        <input type="text" name="name" value="Janusz">
        <br>
        <br>
        <input type="submit" value="Submit">
        </form>  
        
        
        <!--Zadanie 2-->
        <h1>Zadanie2</h1>
        <ul>
        <?php
        //POST
         if(!empty($_POST))
             {
            foreach ($_POST as $key => $value) 
                {
                echo "<li>$key : $value</li>";
             }}
         else { echo "post pusty"; }
        ?>
        </ul>
        <ul>
        <?php
        //GET
        if(!empty($_GET)){
            foreach ($_GET as $key => $value) {
                echo "<li>$key : $value</li>";
            }     
        }
        else {echo "get pusty";}
        ?>
        </ul>
        <?php
        $_GET['a'] = 'a';
        print_r($_REQUEST);
        print_r($_SERVER);
        ?>
        <br><br>
        <hr>
    </body>
</html>
