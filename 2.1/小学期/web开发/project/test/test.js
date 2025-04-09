var stime,smin,ssec;
var etime,emin,esec;
var grade=0;


function start(){
    stime=new Date();
    smin=stime.getMinutes();
    ssec=stime.getSeconds();
    alert("答题开始！")
}

function single1test(){
    var obj=document.single1.steam;
    if(obj[0].checked){
        grade+=1;
    }
    alert("已提交")
}
function single2test(){
    var obj=document.single2.player;
    if(obj[1].checked){
        grade+=1;
    }
    alert("已提交")

}
function single3test(){
    var obj=document.single3.stadium;
    if(obj[2].checked){
        grade+=1;
    }    
    alert("已提交")
}
function multi1test(){
    var obj=document.multi1.team;
    if(obj[0].checked&&obj[2].checked){
        grade+=2;

    }  
    alert("已提交")
}
function multi2test(){
    var obj=document.multi2.team;
    if(obj[ 1].checked&&obj[2].checked){
        grade+=2;
    }   
    alert("已提交")
}

function end(){
    etime=new Date();
    emin=etime.getMinutes();
    esec=etime.getSeconds();
    var rmin,rsec;
    if(esec>=ssec){
        rsec=esec-ssec;
        rmin=emin-smin;
    }
   if(document.writing.fill.value=="失误"){
        grade+=3;
    }   
    document.writing.status.value="1";
    document.writing.grade.value=grade;
    document.writing.name.value=document.fname.name.value;
    document.writing.min.value=rmin;
    document.writing.sec.value=rsec;
    alert("您已完成测试，去看看成绩吧")
}
