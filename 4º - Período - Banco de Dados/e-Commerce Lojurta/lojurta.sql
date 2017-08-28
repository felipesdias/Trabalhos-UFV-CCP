-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 04-Dez-2015 às 10:22
-- Versão do servidor: 5.6.17
-- PHP Version: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `lojurta`
--

--
-- Extraindo dados da tabela `carrinho`
--

INSERT INTO `carrinho` (`idCarrinho`, `Cliente_idCliente`) VALUES
(1, 1),
(3, 1),
(2, 2);

--
-- Extraindo dados da tabela `categoria`
--

INSERT INTO `categoria` (`idCategoria`, `nome`) VALUES
(1, 'Eletronicos'),
(2, 'Roupas'),
(3, 'Sapatos'),
(4, 'Hardware');

--
-- Extraindo dados da tabela `cliente`
--

INSERT INTO `cliente` (`idCliente`, `nome`, `sobrenome`, `login`, `senha`, `email`, `telefone`, `CPF`, `estado`) VALUES
(1, 'Felipe', 'Dias', 'felipe', 'felipe', 'felipe', '12332154', '12612234624', 'MG'),
(2, 'Bruna', 'Dias', 'bruna', 'bruna', 'bruna', '21546584', '12613214523', 'MG'),
(3, 'Teste', 'teste', 'teste', 'teste', 'teste', 'teste', 'teste', 'te');

--
-- Extraindo dados da tabela `endereco`
--

INSERT INTO `endereco` (`idEndereco`, `rua`, `bairro`, `numero`, `complemento`, `CEP`, `ativo`, `cidade`, `UF`, `Cliente_idCliente`) VALUES
(1, 'Tiradentes', 'JoaBras', 245, 'Qualuqer', '36570-000', 1, 'Viçosa', 'MG', 1),
(2, 'Tiradentes', 'JoaBras', 244, NULL, '36570-000', 1, 'Viçosa', 'MG', 2);

--
-- Extraindo dados da tabela `loja`
--

INSERT INTO `loja` (`idLoja`, `nome`, `CNPJ`, `site`, `senha`, `descricao`, `foto`, `data`) VALUES
(2, 'Americanas', 'americanas', 'http://www.americanas.com.br/', 'americanas', 'Lojas Americanas', 'http://jcconcursos.uol.com.br/imagens/informacao/Lojas_Americanas-61227.jpg', '2015-12-03 16:11:02'),
(6, 'Ricardo Eletro', 'ricardo', 'http://ricardoeletro.com.br/', 'ricardo', 'Ricardos Eletrons', 'http://images.maquinadevendas.com.br/site/re/layout/logo_re.png', '2015-12-03 16:12:24');

--
-- Extraindo dados da tabela `produto`
--

INSERT INTO `produto` (`idProduto`, `nome`, `valor`, `estoque`, `descricao`, `foto`, `data`, `Loja_idLoja`, `Categoria_idCategoria`) VALUES
(1, 'Zenfone 2', 1000, 10, 'Celular da Asus', 'http://d3emhpm0gj0nik.cloudfront.net/media/catalog/product/cache/2/small_image/460x460/9df78eab33525d08d6e5fb8d27136e95/a/s/asus_4gb_16gb_ag_1_4_1005290_9583_236_12640_1_9.png', '2015-12-03 16:27:01', 2, 1),
(2, 'Memoria RAM 59415GB', 20.5, 5, 'Memoria mais foda do mundo', 'http://www.informaticashop.com.br/media/catalog/product/cache/1/image/9df78eab33525d08d6e5fb8d27136e95/m/e/mem_ria_ram_ddr3_2gb_-_lenovo_-_55y3710.jpg', '2015-12-03 16:27:51', 2, 4),
(3, 'Sony Xperia Z3', 1120, 30, 'Celular pra nadar com ele', 'http://api.sonymobile.com/files/xperia-z3-tablet-compact-black-1240x840-769dca291eaf20846d5c07bcbf233b34.jpg', '2015-12-03 16:28:36', 2, 1);

--
-- Extraindo dados da tabela `produtonocarrinho`
--

INSERT INTO `produtonocarrinho` (`Produto_idProduto`, `Carrinho_idCarrinho`, `quantidade`) VALUES
(1, 1, 1),
(1, 2, 1),
(1, 3, 1),
(2, 1, 1),
(3, 1, 1),
(3, 3, 2);

--
-- Extraindo dados da tabela `promocao`
--

INSERT INTO `promocao` (`idPromocao`, `nome`, `desconto`, `dataIni`, `dataFim`, `Produto_idProduto`) VALUES
(1, 'memoriam', 20, '2015-12-02 00:00:00', '2015-12-17 00:00:00', 2),
(2, 'xPeria ja foi', 50, '2015-12-01 00:00:00', '2015-12-02 00:00:00', 3);

--
-- Extraindo dados da tabela `venda`
--

INSERT INTO `venda` (`idVenda`, `dataCompra`, `valorTotal`, `formaPagamento`, `Cliente_idCliente`, `Endereço_idEndereco`, `Carrinho_idCarrinho`) VALUES
(1, '2015-12-03 00:00:00', 600, 'Boleto', 1, 1, 1),
(2, '2015-12-04 00:00:00', 253, 'Cartao', 2, 2, 2),
(3, '2015-12-01 00:00:00', 700, 'Deposiuto', 1, 1, 3);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
