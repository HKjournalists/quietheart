var PvTrack;
this.PvTrack||(PvTrack=function(){function A(a,c,b,d){if(a.addEventListener){a.addEventListener(c,b,d);return true}else if(a.attachEvent)return a.attachEvent("on"+c,b);a["on"+c]=b}function p(a,c,b,d,v,g){var k;if(b){k=new Date;k.setTime(k.getTime()+b*6E4)}e.cookie=a+"="+q(c)+(b?";expires="+k.toGMTString():"")+";path="+(d?d:"/")+(v?";domain="+v:"")+(g?";secure":"")}function w(a){return(a=RegExp("(^|;)[ ]*"+a+"=([^;]*)").exec(e.cookie))?B(a[2]):""}function K(){var a=w(x);if(a!=""){a=a.split(".");if(a.length==
5){i=parseInt(a[0]);r=parseInt(a[1]);l=parseInt(a[2]);m=parseInt(a[3]);n=parseInt(a[4]);a=w(y);if(a!="")o=parseInt(a)}}}function L(){var a;a=Math.round((new Date).getTime()/1E3);if(i==0){i=Math.round(Math.random()*2147483647);l=r=a}else l=m;m=a;n=o==0?1:n+1;o=i;a=i+"."+r+"."+l+"."+m+"."+n;if(j==""){p(x,a,C);p(y,o,D)}else{p(x,a,C,"/",j);p(y,o,D,"/",j)}}function M(a){var c=new Image(1,1);c.onLoad=function(){};c.src=a}function E(){if(s=="")return false;if(j=="")return false;if(t=="")return false;return true}
function N(){var a=w(t);return B(a)}function F(){G=true}this.channel=this.pageType=this.type=this.p4=this.p3=this.p2=this.p1=0;var s=this.location=this.referrer="",j="",t="",e=document,h=navigator,H=screen,u=window,I=u.location.hostname,q=u.encodeURIComponent||escape,B=u.decodeURIComponent||unescape,x="__pta",C=1051200,i=0,r=0,l=0,m=0,n=1,y="__pts",o=0,D=20,O=h.cookieEnabled?1:0,P=h.javaEnabled()?1:0,z=false,J="",G=false,f=this;this.track=function(){if(G){if(E()&&z){var a=s+"?v=3.2",c="&p1="+f.p1+
"&p2="+f.p2+"&p3="+f.p3+"&p4="+f.p4+"&t="+f.type+"&cl="+f.channel+"&pt="+f.pageType+"&res="+H.width+"x"+H.height+"&vid="+i+"&vtf="+r+"&vtl="+l+"&vtc="+m+"&vc="+n+"&b=&d=&e=&c=&f="+O+"&g="+P+"&h=",b="-";if(h.plugins&&h.plugins.length)for(var d=0;d<h.plugins.length;d++){if(h.plugins[d].name.indexOf("Shockwave Flash")!=-1){b=h.plugins[d].description.split("Shockwave Flash ")[1];break}}else if(u.ActiveXObject)for(d=10;d>=2;d--)try{if(eval("new ActiveXObject('ShockwaveFlash.ShockwaveFlash."+d+"');")){b=
d+".0";break}}catch(v){}d=q;var g;if(f.referrer!="")g=f.referrer;else{g="";try{g=top.document.referrer}catch(k){if(parent)try{g=parent.document.referrer}catch(Q){g=""}}if(g==="")g=e.referrer}a+=c+b+"&i="+d(g)+"&k="+q(f.location!=""?f.location:e.location.href)+"&uid="+q(J)+"&rand="+Math.random();M(a)}}else setTimeout(arguments.callee,0)};(function(){for(var a=["pcpop.com"],c=["it168.com","qudao168.com","chinaunix.com","chinaunix.net","itpub.net","ixpub.net","igeek.com.cn","afjk.com","app111.com","mobpub.net","jimi168.com"],b=0;b<a.length;b++)if(I.indexOf(a[b])>
-1){j=a[b];s="http://count.pcpop.com/count.ashx";t="pop_userid";return}for(b=0;b<c.length;b++)if(I.indexOf(c[b])>-1){j=c[b];s="http://stat.it168.com/count.ashx";t="sso_username_utf8";break}})();A(e,"mouseover",F,false);A(e,"mousemove",F,false);z=function(){var a,c;if(e.body){a=e.body.clientWidth|e.documentElement.clientWidth;c=e.body.clientHeight|e.documentElement.clientHeight}else{a=e.documentElement.clientWidth;c=e.documentElement.clientHeight}if(a>300&&c>300)return true;return false}();if(E()&&
z)try{K();L();J=N()}catch(R){}});
