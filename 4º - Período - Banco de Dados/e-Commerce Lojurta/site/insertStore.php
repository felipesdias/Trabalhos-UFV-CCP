<?php
if (isset($_POST['name']) && isset($_POST['description']) && isset($_POST['CNPJ']) && isset($_POST['password']) && isset($_POST['web'])) {
		$name = $_POST['name'];
		$description = $_POST['description'];
		$CNPJ = $_POST['CNPJ'];
		$password = $_POST['password'];
		$web = $_POST['web'];
		$imagi = $_POST['imagi'];
}
else{
	$newStore = false;
	require_once("registerLoja.php");
}

//Faz conexao com o banco
include 'dbConnection.php';
$date = date('Y/m/d H:i:s');
// sql para inserir dados na tabela loja

$sql = "INSERT INTO loja(nome, CNPJ, site, senha, descricao, foto, data) VALUES('$name','$CNPJ','$web','$password','$description','$imagi','$date')";

if ($link->query($sql) === TRUE) {
    $newStore = true;
} else {
    $newStore = false;
}

$link->close();

require_once("registerLoja.php");

?>