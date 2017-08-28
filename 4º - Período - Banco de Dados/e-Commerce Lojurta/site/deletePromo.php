<?php
if (isset($_POST['promo'])) {         
		$promo = $_POST['promo'];
}
else{
	header("Location: gerenPromo.php"); exit;
}
//Faz conexao com o banco
include 'dbConnection.php';		


// sql para inserir dados na tabela produto
$sql = "DELETE FROM promocao
		WHERE idPromocao = $promo";


if ($link->query($sql) === TRUE) {
    $deletePromo = true;
} else {
    $deletePromo = false;
}

$link->close();

require_once("gerenPromo.php");

?>