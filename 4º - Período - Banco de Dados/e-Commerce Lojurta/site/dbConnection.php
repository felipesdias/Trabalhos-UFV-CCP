<?php
$link = mysqli_connect('localhost', 'root', '', 'lojurta');
if (!$link) {
    die('Não foi possível conectar: ' . mysqli_error());
}
//echo 'Conexão bem sucedida';


//CONEXAO COM O BD
$db_selected = mysqli_select_db($link,'lojurta');
if (!$db_selected) {
    die ('Can\'t use lojurta : ' . mysqli_error($link));
}

/////////////////
/// Consultas ///
/////////////////

//Listar Categorias
$ListarCategorias = mysqli_query($link,"SELECT *
									FROM categoria");

//Listar Lojas
$listarLojas = mysqli_query($link,"SELECT *
									FROM loja");
									
$listaTopCli = mysqli_query($link,"SELECT Cliente_idCliente, SUM(valorTotal), nome, sobrenome
										FROM venda, cliente
										WHERE Cliente_idCliente = idCliente
										GROUP BY Cliente_idCliente
									");				




							
									
$listarLojas2 = mysqli_query($link,"SELECT *
									FROM loja");
									
$listarLojas3 = mysqli_query($link,"SELECT *
									FROM loja");
									
$promoPromo = mysqli_query($link,"SELECT *
							 FROM produto");
?>
