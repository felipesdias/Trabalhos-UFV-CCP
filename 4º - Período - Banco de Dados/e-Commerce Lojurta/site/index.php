<!doctype html>
<html class="no-js">

	<head>
		<meta charset="utf-8"/>
		<title>FOLDER TEMPLATE</title>
		 
		<!--[if lt IE 9]>
			<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
		<![endif]-->
		<link rel="stylesheet" media="all" href="css/style.css"/>
		<meta name="viewport" content="width=device-width, initial-scale=1"/>
		<!-- Adding "maximum-scale=1" fixes the Mobile Safari auto-zoom bug: http://filamentgroup.com/examples/iosScaleBug/ -->		
				
		<!-- JS -->
		<script src="js/jquery-1.7.1.min.js"></script>
		<script src="js/custom.js"></script>
		<script src="js/tabs.js"></script>
		<script src="js/css3-mediaqueries.js"></script>
		<script src="js/jquery.columnizer.min.js"></script>
		
		<!-- Isotope -->
		<script src="js/jquery.isotope.min.js"></script>
		
		<!-- Lof slider -->
		<script src="js/jquery.easing.js"></script>
		<script src="js/lof-slider.js"></script>
		<link rel="stylesheet" href="css/lof-slider.css" media="all"  /> 
		<!-- ENDS slider -->
		
		<!-- Tweet -->
		<link rel="stylesheet" href="css/jquery.tweet.css" media="all"  /> 
		<script src="js/tweet/jquery.tweet.js" ></script> 
		<!-- ENDS Tweet -->
		
		<!-- superfish -->
		<link rel="stylesheet" media="screen" href="css/superfish.css" /> 
		<script  src="js/superfish-1.4.8/js/hoverIntent.js"></script>
		<script  src="js/superfish-1.4.8/js/superfish.js"></script>
		<script  src="js/superfish-1.4.8/js/supersubs.js"></script>
		<!-- ENDS superfish -->
		
		<!-- prettyPhoto -->
		<script  src="js/prettyPhoto/js/jquery.prettyPhoto.js"></script>
		<link rel="stylesheet" href="js/prettyPhoto/css/prettyPhoto.css"  media="screen" />
		<!-- ENDS prettyPhoto -->
		
		<!-- poshytip -->
		<link rel="stylesheet" href="js/poshytip-1.1/src/tip-twitter/tip-twitter.css"  />
		<link rel="stylesheet" href="js/poshytip-1.1/src/tip-yellowsimple/tip-yellowsimple.css"  />
		<script  src="js/poshytip-1.1/src/jquery.poshytip.min.js"></script>
		<!-- ENDS poshytip -->
		
		<!-- JCarousel -->
		<script type="text/javascript" src="js/jquery.jcarousel.min.js"></script>
		<link rel="stylesheet" media="screen" href="css/carousel.css" /> 
		<!-- ENDS JCarousel -->
		
		<!-- GOOGLE FONTS -->
		<link href='http://fonts.googleapis.com/css?family=Voltaire' rel='stylesheet' type='text/css'>

		<!-- modernizr -->
		<script src="js/modernizr.js"></script>
		
		<!-- SKIN -->
		<link rel="stylesheet" media="all" href="css/skin.css"/>
		
		<!-- Less framework -->
		<link rel="stylesheet" media="all" href="css/lessframework.css"/>
		
		<!-- flexslider -->
		<link rel="stylesheet" href="css/flexslider.css" >
		<script src="js/jquery.flexslider.js"></script>

	</head>
	
	<!-- ALERTA DE LOGIN INVALIDO -->
	<?php
		if(isset($valide)){
			if(!$valide){
				echo"<script type='text/javascript'>";
				echo "alert('Login inválido.');";
				echo "</script>";
			}
		}
	?>
	
	<body class="home">
	
		<!-- HEADER -->
		<header>
			<div class="wrapper cf">
				
				<div id="logo">
					<a href="index.php"><img  src="img/logo.png" alt="Simpler"></a>
				</div>
				
				<!-- nav -->
	<ul id="nav" class="sf-menu">
	<li ><a href="index.php">HOME</a></li>
<?php
session_start();

if(!(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'loja')) {
	echo '<li><a href="products.php">PRODUTOS</a></li>';
	echo '<li><a href="#">LOJAS</a></li>';
}

if(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'cliente') {
	echo '<li><a href="history.php">HISTÓRICO</a></li>';
	echo '<li><a href="car.php">CARRINHO</a></li>';
}

if(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'loja') {
	echo '<li><a href="#">HISTORICO</a></li>';
	echo '<li><a href="registerProducts.php">CADASTRAR PRODUTO</a></li>';
	echo '<li><a href="gerenPromo.php">GERENCIAR PROMOÇÃO</a></li>';
}
?>

					
					<li><a href="contact.php">CONTATO</a></li>
<?php
	if(!(isset($_SESSION['tipo']))) {
				echo<<< HTML
					<li><a href="#">LOGIN</a>
						<ul>
							<li>
								<script type="text/javascript" src="js/form-validation.js"></script>
								<table>
									<tr>
										<td>
											<form action="validate.php" method="POST">
											<fieldset style="width:100px" size="100">
												Usuário 							
												<input name="user"  id="user" type="text" class="form-poshytip" size="7"/>
												<p>
												Senha <input name="password"  id="password" type="password" class="form-poshytip" size="7"/>
											<input name="enviar"  id="enviar" type="submit" class="form-poshytip" />
											<a href="registerCliente.php">Cadastrar cliente </a>
											</fieldset>
											</form>
											</script>
										</td>
										<td>								
											<script type="text/javascript" src="js/form-validation.js"></script>
											<form action="validate.php" method="POST">
											<fieldset>
												CNPJ 							
												<input name="CNPJ"  id="CNPJ" type="text" class="form-poshytip" size="7"/>
												<p>
												Senha <input name="senha"  id="senha" type="password" class="form-poshytip" size="7"/>
											<input name="enviar"  id="enviar" type="submit" class="form-poshytip" />
											<a href="registerLoja.php">Cadastrar loja </a>
											</fieldset>
											</form>
											</script>
										</td>
									</tr>
								</table>
							</li>
						</ul>
						
					</li>
HTML;
	} else {
		echo '<li><a href="logout.php">SAIR</a></li>';
	}
?>
				</ul>
				
				<div id="combo-holder"></div>
				<!-- ends nav -->
				
				
				





			</div>
		</header>
		<!-- ENDS HEADER -->
		
		<!-- MAIN -->
		<div id="main">
			<div class="wrapper cf">
			
			
			
			
				
			<!-- featured -->
			<div class="home-featured">
				<ul id="filter-buttons">
					<li><a href="#" data-filter=".lojas" >Lojas</a></li>
					<li><a href="#" data-filter=".pomocoes">Promoções por Loja</a></li>
					<li><a href="#" data-filter=".categoria">Produtos por Categoria</a></li>
					<li><a href="#" data-filter=".prodLoja">Produtos por Loja</a></li>
					<li><a href="#" data-filter=".topCli">Top Clientes</a></li>
					<li><a href="#" data-filter=".spMGcli">Super Clientes Minas</a></li>
				</ul>
				
				<!-- Filter container -->
			<div id='filter-container' class='cf'>
				<?php
					//Faz conexao com o banco
					include 'dbConnection.php';
					
					while($escrever=mysqli_fetch_array($listarLojas)) {
						echo "<figure class='lojas'>
								<a href=".$escrever['site']." class='thumb'><img src='".$escrever['foto']."' alt='alt' /></a>
								<figcaption>
									<a href=".$escrever['site']."><h3 class='heading'>".$escrever['nome']." </h3></a>"
										.$escrever['descricao']."
								</figure>
							";	
					}
					
					while($escrever2=mysqli_fetch_array($listarLojas2)){
						echo "<figure class='pomocoes'>
								<a href='index.php?loja=".$escrever2['idLoja']."' class='thumb'><img src='".$escrever2['foto']."' alt='alt' /></a>
								<figcaption>
									<a href='index.php?loja=".$escrever2['idLoja']."'><h3 class='heading'>".$escrever2['nome']." </h3></a>"
										.$escrever2['descricao']."
								</figure>
							";
					}
			
					while($escreve3=mysqli_fetch_array($ListarCategorias)){
						echo "<figure class='categoria'>
								<figcaption>
									<a href='index.php?categoria=".$escreve3['idCategoria']."'><h3 class='heading'>".$escreve3['nome']." </h3></a>
								</figure>
							";
					}

					while($escrever4=mysqli_fetch_array($listarLojas3)){
						echo "<figure class='prodLoja'>
								<a href='index.php?loja2=".$escrever4['idLoja']."' class='thumb'><img src='".$escrever4['foto']."' alt='alt' /></a>
								<figcaption>
									<a href='index.php?loja2=".$escrever4['idLoja']."'><h3 class='heading'>".$escrever4['nome']." </h3></a>"
										.$escrever4['descricao']."
								</figure>
							";
					}
			
					while($escrever5=mysqli_fetch_array($listaTopCli)){
						echo "<figure class='topCli'>
								<figcaption>
									<a><h3 class='heading'>".$escrever5['nome']." ".$escrever5['sobrenome']." - ".$escrever5['SUM(valorTotal)']."</h3></a>
								</figure>
							";	
					}
					
$listaspMGcli = mysqli_query($link,"CREATE TEMPORARY TABLE VendaTotal SELECT Cliente_idCliente, SUM(valorTotal) as valorTotal
										FROM venda
										GROUP BY Cliente_idCliente;
                                       
SELECT nome, sobrenome
FROM cliente, VendaTotal
WHERE idCliente = Cliente_idCliente and valorTotal > 999 and estado = 'MG'
									");
					
					while($escrever6=mysqli_fetch_array($listaspMGcli)){
						echo "<figure class='spMGcli'>
								<figcaption>
									<a><h3 class='heading'>".$escrever6['nome']." ".$escrever6['sobrenome']."</h3></a>
								</figure>
							";	
					}
				?>

			</div>
			
			<div id='filter-container' class='cf'>
			<?php 
					if(isset($_GET["loja2"])) {
						$produtoLoja = mysqli_query($link,"SELECT *
															FROM loja L, produto P
															WHERE P.Loja_idLoja = L.idLoja and P.Loja_idLoja = ".$_GET["loja2"]."
															ORDER BY P.Categoria_idCategoria ASC
															");
						$dataAtual2 = date('Y/m/d H:i:s');
						while($escrever4=mysqli_fetch_array($produtoLoja)){
							//
							$temDesconto2 = mysqli_query($link, "SELECT *
																	FROM promocao
																	WHERE Produto_idProduto = ".$escrever4['idProduto']." and '".$dataAtual2."' BETWEEN dataIni and dataFim 
							");
							
							if($aux2=mysqli_fetch_array($temDesconto2)) {
								$novoValor2 = $escrever4['valor'] * ( (100-$aux2['desconto'])/100 );
							
								echo "<figure class='prodLoja'>
									<a class='thumb'><img src='".$escrever4['foto']."' alt='alt' /></a>
									<figcaption>
										<a ><h3 class='heading'>".$escrever4['nome']."</h3></a>Valor: de R$ ".$escrever4['valor']." por R$ ".$novoValor2."
									</figure>
								";	
							} else {
								
							echo "<figure class='prodLoja'>
									<a class='thumb'><img src='".$escrever4['foto']."' alt='alt' /></a>
									<figcaption>
										<a ><h3 class='heading'>".$escrever4['nome']."</h3></a>Valor: R$ ".$escrever4['valor']."
									</figure>
								";	
							}
						}
					} elseif(isset($_GET["categoria"])) {
						$produtoCategoria = mysqli_query($link,"SELECT *
															FROM categoria C, produto P
															WHERE P.Categoria_idCategoria = C.idCategoria and P.Categoria_idCategoria = ".$_GET["categoria"]."");
									
						$dataAtual = date('Y/m/d H:i:s');
						while($escreve3=mysqli_fetch_array($produtoCategoria)){
							//
							$temDesconto = mysqli_query($link, "SELECT *
																	FROM promocao
																	WHERE Produto_idProduto = ".$escreve3['idProduto']." and '".$dataAtual."' BETWEEN dataIni and dataFim 
							");
							
							if($aux=mysqli_fetch_array($temDesconto)) {
								$novoValor = ($escreve3['valor'] * ( (100-$aux['desconto'])/100 ));
							
								echo "<figure class='categoria'>
									<a class='thumb'><img src='".$escreve3['foto']."' alt='alt' /></a>
									<figcaption>
										<a ><h3 class='heading'>".$escreve3['nome']."</h3></a>Valor: de R$ ".$escreve3['valor']." por R$ ".$novoValor."
									</figure>
								";	
							} else {
								
							echo "<figure class='categoria'>
									<a class='thumb'><img src='".$escreve3['foto']."' alt='alt' /></a>
									<figcaption>
										<a ><h3 class='heading'>".$escreve3['nome']."</h3></a>Valor: R$ ".$escreve3['valor']."
									</figure>
								";	
							}
						}
					} elseif(isset($_GET["loja"])) {
						$promoLoja = mysqli_query($link,"SELECT *
															FROM loja L, promocao D, produto P
															WHERE P.Loja_idLoja = L.idLoja and D.Produto_idProduto = P.idProduto and L.idLoja = ".$_GET["loja"]."");
															
						while($escrever2=mysqli_fetch_array($promoLoja)){
							$novoValor = $escrever2['valor'] * ( (100-$escrever2['desconto'])/100 );
							echo "<figure class='pomocoes'>
									<a class='thumb'><img src='".$escrever2['foto']."' alt='alt' /></a>
									<figcaption>
										<a ><h3 class='heading'>".$escrever2['nome']."</h3></a> Valor: de R$ ".$escrever2['valor']." por R$ ".$novoValor." <br>Inicio: ".$escrever2['dataIni']."<br>Fim: ".$escrever2['dataFim']."
									</figure>
								";	
						}
					}
			?>
			</div>
			</div>
			<!-- ENDS featured -->
			
			
			
			
			</div><!-- ENDS WRAPPER -->
		</div>
		<!-- ENDS MAIN -->
		
		
		
	</body>
	
	
	
</html>