<?php
//Faz conexao com o banco
include 'dbConnection.php';
	
// sql para inserir dados na tabela loja
$sql = "INSERT INTO loja(nome, descricao, CNPJ, site, dataCadstro, nivelPrioridade, foto) VALUES(
		'$name',
		'$description',
		'$CNPJ',
		'$web',
		'$date',
		'$nivel',
		'$pic'
)";

?>
