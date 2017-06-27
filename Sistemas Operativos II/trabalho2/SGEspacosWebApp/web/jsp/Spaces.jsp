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
        <title>Espacos Disponiveis</title>
        <link rel="stylesheet" href="css/eshop.css" type="text/css"/>
    </head>
    <body>
        <jsp:include page="TopMenu.jsp" flush="true"/>
        <jsp:include page="LeftMenu.jsp" flush="true"/>
        <div class="content">
            <h2>Espacos do CDPG</h2>
            <table class="tg">
                <tr>
                    <th>Nome do Espaco</th>
                    <th>Hora de abertura</th>
                    <th>Hora de fecho</th>
                    <th>Custo por hora</th>
                </tr>
                <%
                    try {
                        Vector<Espaco> spaces = dataManager.getSpaceList();
                        if (spaces != null) {
                            for (Espaco e : spaces) {
                                out.println(
                                        "<tr>"
                                        + "<td>" + e.getName() + "</td>"
                                        + "<td>" + e.getOpenT() + "</td>"
                                        + "<td>" + e.getCloseT() + "</td>"
                                        + "<td>" + String.valueOf(e.getCost()) + "</td>"
                                        + "</tr>");
                            }
                        }
                    } catch (Exception e) {
                %><p class="error">Invalid book identifier!</p><%
                    }
                %>
            </table>
        </div>  <!-- final da seccao de content -->
    </body>
</html>
