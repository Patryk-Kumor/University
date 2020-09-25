<html>
    <head></head>
<body>


Imie: <?php echo $_POST["name"]; ?><br>


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
        echo "<br><br>";
        //print_r($_SERVER);
        ?>
        <br><br>
        <hr>
</body>

</html>