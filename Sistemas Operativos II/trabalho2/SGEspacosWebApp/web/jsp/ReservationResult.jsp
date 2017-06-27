<%@page import="eshop.beans.Reserva"%>
<%@page import="java.util.Vector"%>
<%@page language="java" contentType="text/html"%>
<%@page import="eshop.beans.Espaco"%>

<%-- Isto é um comentário JSP... --%>
<%-- a indicacao abaixo disponibiliza a variável dataManager, para acesso aos dados --%>
<jsp:useBean id="dataManager" scope="application" class="eshop.model.DataManager"/>

<%
    String base = (String) application.getAttribute("base");
    String imageURL = (String) application.getAttribute("imageURL");
%>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <title>Reservar Espaco</title>
        <link rel="stylesheet" href="css/eshop.css" type="text/css"/>
    </head>
    <body>
        <jsp:include page="TopMenu.jsp" flush="true"/>
        <jsp:include page="LeftMenu.jsp" flush="true"/>
        <div class="content">
            <%
                String nomeResp = request.getParameter("nomeresp");
                String tlfResp = request.getParameter("tlfresp");
                String numPessoas = request.getParameter("numpessoas");
                String codEsp = request.getParameter("space");
                String date = request.getParameter("date");
                String horaI = request.getParameter("timestart");
                String duration = request.getParameter("duration");
                int custo = dataManager.getCost(codEsp);
                int custoRes = custo * Integer.parseInt(duration);

                int temp = Integer.parseInt(horaI.split(":")[0]);
                temp += Integer.parseInt(duration);
                String horaF = String.valueOf(temp) + ":00:00";

                String dataInicio = String.format("%s %s", date, horaI);
                String dataFim = String.format("%s %s", date, horaF);
                
                int codReserva = dataManager.makeReservation(nomeResp, tlfResp, custoRes, Integer.parseInt(numPessoas), codEsp, dataInicio, dataFim);
                System.out.println(codReserva);
                if (codReserva != -1) {
            %><p>Espaço Reservado!</p><br><p>Codigo da reserva: <%=codReserva%><b></b></p><%
            } else {
            %> <p>Espaço indisponivel para reserva. Verifique se o espaço está disponivel antes de reservar</p> <%
                }
            %>
        </div>  <!-- final da seccao de content -->
    </body>
</html>
