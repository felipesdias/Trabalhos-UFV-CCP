<?php
if (isset($_POST['name']) && isset($_POST['value']) && isset($_POST['stock'])
	&& isset($_POST['imagi']) && isset($_POST['category'])) {
              
		$name = $_POST['name'];
		$description = $_POST['description'];
		$value = $_POST['value'];
		$stock = $_POST['stock'];
		$imagi = $_POST['imagi'];
		$idSubCategoria = $_POST['category'];
		
}
else{
	header("Location: registerProducts.php"); exit;
}
//Faz conexao com o banco
include 'dbConnection.php';
session_start();

$cnpj = $_SESSION['login'];
$idLoja = mysqli_query($link,"SELECT * 
										FROM loja
										WHERE CNPJ='".$cnpj."'");
						
$aux = mysqli_fetch_assoc($idLoja);
$aux2 = $aux['idLoja'];		
$date = date('Y/m/d H:i:s');

// sql para inserir dados na tabela produto
$sql = "INSERT INTO produto(nome, valor, estoque, descricao, foto, data, Loja_idLoja, Categoria_idCategoria) VALUES(
		'$name',
		'$value',
		'$stock',
		'$description',
		'$imagi',
		'$date',
		'$aux2',
		'$idSubCategoria'
)";

if ($link->query($sql) === TRUE) {
    $newProduto = true;
} else {
    $newProduto = false;
}

$link->close();

require_once("registerProducts.php");

?>