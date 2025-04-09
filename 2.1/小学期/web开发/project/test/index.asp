<!DOCTYPE html>
<%@LANGUAGE="VBSCRIPT" CODEPAGE="65001" %>

<html>
<%
dim status
status="0"
set conn=Server.CreateObject("ADODB.Connection")
conn.Provider="Microsoft.Jet.OLEDB.4.0"
conn.Open "C:\Users\LBZ\Desktop\project\test\score.mdb"
%>
<head>
    <title>足球小测试</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <link rel="stylesheet" type="text/css" href="test.css">
    <script type="text/javascript" src="test.js"></script>
</head>

<body>
    <h1>欢迎参加本次足球小测验</h1>
    <div id="beginning">
        <p>访问时间
            <script type="text/javascript">
                document.write(new Date());
            </script>
        </p>
        <p>本次小测验共分有三道大题，分别为单选题，多选题以及填空题，满分10分</p>
        <p>准备好了吗？我们开始吧！<br />请输入您的昵称，点击开始进行答题</p>
        <form name="fname">
            <input type="text" name="name" size="5" maxlength="5" />
            <input type="button" name="begin" value="开始" onclick="start()" />
        </form>
    </div>


    <div id="single">
        <h2>一、单选题</h2>
        <p class="intro">本部分为单选题，请根据问题选择唯一正确的答案，共3题</p>
        <fieldset>
            <legend>单选题（1分/题）</legend>
            <div>
                <h3>1.请问下图是哪只英超球队的队徽</h3>
                <div class="lp">
                    <img src="img/single/1.jpg" alt="第一题" width="150px" />
                </div>
                <form name="single1">
                    <p><input type="radio" name="steam" value="利物浦" />利物浦</p>
                    <p><input type="radio" name="steam" value="曼彻斯特联" />曼彻斯特联</p>
                    <p><input type="radio" name="steam" value="纽卡斯尔联" />纽卡斯尔联</p>
                    <input type="button" value="提交" onclick="single1test()" />
                </form>
            </div>

            <div>
                <h3>2.请问下图是哪位英国足球运动员</h3>
                <div class="lp">
                    <img src="img/single/2.jpg" alt="第二题" width="160px" />
                </div>
                <form name="single2">
                    <p><input type="radio" name="player" value="德布劳内" />德布劳内</p>
                    <p><input type="radio" name="player" value="欧文" />欧文</p>
                    <p><input type="radio" name="player" value="贝克汉姆" />贝克汉姆</p>
                    <input type="button" value="提交" onclick="single2test()" />
                </form>
            </div>

            <div>
                <h3>3.请问下图是哪座著名的欧洲足球场</h3>
                <div float="left">
                    <img src="img/single/3.jpg" alt="第三题" width="280px" />
                </div>
                <form name="single3">
                    <p><input type="radio" name="stadium" value="白鹿巷球场" />白鹿巷球场</p>
                    <p><input type="radio" name="stadium" value="安联球场" />安联球场</p>
                    <p><input type="radio" name="stadium" value="诺坎普球场" />诺坎普球场</p>
                    <input type="button" value="提交" onclick="single3test()" />
                </form>
            </div>
        </fieldset>
<h2>二、多选题</h2>
<p class="intro">本部分为多选题，请根据问题选择多个正确的答案，共2题</p>
<fieldset>
    <legend>多选题（2分/题）</legend>
    <div>
        <h3>1.请问下列哪些男子足球国家队获得过世界杯冠军</h3>
        <form name="multi1">
            <p><input type="checkbox" name="team" value="德国" />德国</p>
            <p><input type="checkbox" name="team" value="美国" />美国</p>
            <p><input type="checkbox" name="team" value="法国" />法国</p>
            <p><input type="checkbox" name="team" value="葡萄牙" />葡萄牙</p>
            <input type="button" value="提交" onclick="multi1test()" />
        </form>
    </div>
    <div>
        <h3>2.请问葡萄牙球星C罗效力过以下哪些球队</h3>
        <form name="multi2">
            <p><input type="checkbox" name="team" value="波尔图" />波尔图</p>
            <p><input type="checkbox" name="team" value="尤文图斯" />尤文图斯</p>
            <p><input type="checkbox" name="team" value="皇家马德里" />皇家马德里</p>
            <p><input type="checkbox" name="team" value="拜仁慕尼黑" />拜仁慕尼黑</p>
            <input type="button" value="提交" onclick="multi2test()" />
        </form>
    </div>
</fieldset>
<h2>三、填空题</h2>
<p class="intro">本部分为填空题，请在文本框内输入正确答案，共1题</p>
<fieldset>
    <legend>填空题（3分/题）</legend>
    <div>
        <h3>看图写话（不超过5个字符）</h3>
        <div class="lp">
            <img src="img/fill/1.jpg" alt="最后一题" width="300px">
        </div>
        <form name="writing" action="index.asp" method="post">
            <p>巨大巨大超级超级低级的<input type="text" size="5" maxlength="5" name="fill" /></p>
            <input type="hidden" name="status"  value="0"/>
            <input type="hidden" name="grade" />
            <input type="hidden" name="name" />
            <input type="hidden" name="min"/>
            <input type="hidden" name="sec"/>
            <input type="submit" value="提交" onclick="end()" />
        </form>
    </div>
</fieldset>

<% 
   status=trim(request.form("status"))<!--判断提交-->
   If StrComp(status,"1")=0 Then
    grade=trim(request.form("grade"))
    name=trim(request.form("name"))
    min=trim(request.form("min"))
    sec=trim(request.form("sec"))
    <!--写入过程-->
    str="INSERT INTO score (s_name,s_score) "
    str=str&"VALUES "
    str=str&"('"&name&"','"&grade&"')"
    conn.Execute str
    <!--呈现过程-->
    Response.write("<div id="&chr(34)&"result"&chr(34)&">")
    Response.write("<p>用户："&name&"</p>")
    Response.write("<p>成绩："&grade&"/10</p>")
    Response.write("<p>用时："&min&"分钟"&sec&"秒</p>")
    Response.write("</div>")
    <!--表格部分（按成绩降序）-->
    set rs=CreateObject("ADODB.recordset")
    rs.Open "SELECT * FROM score ORDER BY s_score DESC",conn
    Response.write("<h2>排行榜</h2>")
    Response.write "<table>"
        Response.write "<th>"
            Response.write("<td><p>用户名</p></td>")
            Response.write("<td><p>成绩</p></td>")
        Response.write "</th>"
        do Until rs.EOF
            Response.write "<tr>"
            for each x in rs.Fields
                Response.write "<td>"
                    Response.write(x.value)
                Response.write "</td>"
            next
            rs.MoveNext    
            Response.write "</tr>"
        loop
   Response.write "</table>"
   rs.close
   conn.close
   End If
%>      
</body>

</html>