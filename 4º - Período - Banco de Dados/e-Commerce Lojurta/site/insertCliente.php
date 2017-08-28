<?php
if (isset($_POST['name']) && isset($_POST['name2']) && isset($_POST['usuario']) && isset($_POST['password'])
	and isset($_POST['email'])and isset($_POST['tel']) && isset($_POST['CPF']) && isset($_POST['estado'])) {
              
		$name = $_POST['name'];
		$name2 = $_POST['name2'];
		$usuario = $_POST['usuario'];
		$password = $_POST['password'];
		$email = $_POST['email'];
		$tel = $_POST['tel'];
		$CPF = $_POST['CPF'];
		$estado = $_POST['estado'];
}
else{
	$newCliente = false;
	require_once("registerCliente.php"); exit;
}

//Faz conexao com o banco
include 'dbConnection.php';
	
// sql para inserir dados na tabela loja
$sql = "INSERT INTO cliente(nome, sobrenome, login, senha, email, telefone, CPF, estado) VALUES(
		'$name',
		'$name2',
		'$usuario',
		'$password',
		'$email',
		'$tel',
		'$CPF',
		'$estado'
)";

if ($link->query($sql) === TRUE) {
    $newCliente = true;
} else {
    $newCliente = false;
}

$link->close();

require_once("registerCliente.php");

?>