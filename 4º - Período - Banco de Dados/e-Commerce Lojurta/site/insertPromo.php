<?php
if (isset($_POST['nombre']) && isset($_POST['produto']) && isset($_POST['desconto'])
	&& isset($_POST['dateIni']) && isset($_POST['dateFim']) && isset($_POST['horaIni']) && isset($_POST['horaFim'])) {
              
		$nombre = $_POST['nombre'];
		$produto = $_POST['produto'];
		$desconto = $_POST['desconto'];
		$dateIni = $_POST['dateIni'];
		$dateFim = $_POST['dateFim'];
		$horaIni = $_POST['horaIni'];
		$horaFim = $_POST['horaFim'];
}
else{
	header("Location: gerenPromo.php"); exit;
}
//Faz conexao com o banco
include 'dbConnection.php';		

$dateIni = $dateIni." ".$horaIni.":00";
$dateFim = $dateFim." ".$horaFim.":00";


// sql para inserir dados na tabela produto
$sql = "INSERT INTO promocao(nome, desconto, dataIni, dataFim, Produto_idProduto) VALUES(
		'$nombre',
		'$desconto',
		'$dateIni',
		'$dateFim',
		'$produto'
)";

if ($link->query($sql) === TRUE) {
    $newPromo = true;
} else {
    $newPromo = false;
}

$link->close();

require_once("gerenPromo.php");

?>