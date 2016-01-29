function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Phi */
	this.urlHashMap["rtwdemo_roll:1"] = "rtwdemo_roll.c:55,132&rtwdemo_roll.h:48";
	/* <Root>/Psi */
	this.urlHashMap["rtwdemo_roll:2"] = "rtwdemo_roll.c:78&rtwdemo_roll.h:49";
	/* <Root>/P */
	this.urlHashMap["rtwdemo_roll:3"] = "rtwdemo_roll.c:148&rtwdemo_roll.h:50";
	/* <Root>/TAS */
	this.urlHashMap["rtwdemo_roll:4"] = "rtwdemo_roll.c:79&rtwdemo_roll.h:51";
	/* <Root>/AP_Eng */
	this.urlHashMap["rtwdemo_roll:5"] = "rtwdemo_roll.c:47,105,178&rtwdemo_roll.h:52";
	/* <Root>/HDG_Mode */
	this.urlHashMap["rtwdemo_roll:6"] = "rtwdemo_roll.c:76&rtwdemo_roll.h:53";
	/* <Root>/HDG_Ref */
	this.urlHashMap["rtwdemo_roll:7"] = "rtwdemo_roll.c:77&rtwdemo_roll.h:54";
	/* <Root>/Turn_Knob */
	this.urlHashMap["rtwdemo_roll:8"] = "rtwdemo_roll.c:80&rtwdemo_roll.h:55";
	/* <Root>/BasicRollMode */
	this.urlHashMap["rtwdemo_roll:74"] = "rtwdemo_roll.c:103,175,181,198";
	/* <Root>/EngSwitch */
	this.urlHashMap["rtwdemo_roll:10"] = "rtwdemo_roll.c:177,207";
	/* <Root>/HeadingMode */
	this.urlHashMap["rtwdemo_roll:52"] = "rtwdemo_roll.c:87,91";
	/* <Root>/ModeSwitch */
	this.urlHashMap["rtwdemo_roll:12"] = "rtwdemo_roll.c:72,101";
	/* <Root>/RollAngleReference */
	this.urlHashMap["rtwdemo_roll:14"] = "rtwdemo_roll.c:42,70,93,98";
	/* <Root>/Zero */
	this.urlHashMap["rtwdemo_roll:32"] = "rtwdemo_roll.c:201";
	/* <Root>/Ail_Cmd */
	this.urlHashMap["rtwdemo_roll:33"] = "rtwdemo_roll.c:185,191,202&rtwdemo_roll.h:60";
	/* <S1>/CmdLimit */
	this.urlHashMap["rtwdemo_roll:81"] = "rtwdemo_roll.c:182,197";
	/* <S1>/DispGain */
	this.urlHashMap["rtwdemo_roll:82"] = "rtwdemo_roll.c:131";
	/* <S1>/DispLimit */
	this.urlHashMap["rtwdemo_roll:83"] = "rtwdemo_roll.c:122,133";
	/* <S1>/IntGain */
	this.urlHashMap["rtwdemo_roll:84"] = "rtwdemo_roll.c:161";
	/* <S1>/Integrator */
	this.urlHashMap["rtwdemo_roll:85"] = "rtwdemo_roll.c:109,154,160,174&rtwdemo_roll.h:42,43";
	/* <S1>/NotEngaged */
	this.urlHashMap["rtwdemo_roll:86"] = "rtwdemo_roll.c:104";
	/* <S1>/RateGain */
	this.urlHashMap["rtwdemo_roll:87"] = "rtwdemo_roll.c:155";
	/* <S1>/RateLimit */
	this.urlHashMap["rtwdemo_roll:88"] = "rtwdemo_roll.c:138,149";
	/* <S1>/Sum */
	this.urlHashMap["rtwdemo_roll:89"] = "rtwdemo_roll.c:134";
	/* <S1>/Sum1 */
	this.urlHashMap["rtwdemo_roll:90"] = "rtwdemo_roll.c:147";
	/* <S1>/Sum2 */
	this.urlHashMap["rtwdemo_roll:91"] = "rtwdemo_roll.c:153,184,190,200";
	/* <S2>/DispGain */
	this.urlHashMap["rtwdemo_roll:56"] = "rtwdemo_roll.c:75";
	/* <S2>/Product */
	this.urlHashMap["rtwdemo_roll:57"] = "rtwdemo_roll.c:81";
	/* <S2>/Sum */
	this.urlHashMap["rtwdemo_roll:58"] = "rtwdemo_roll.c:83";
	/* <S3>/Abs */
	this.urlHashMap["rtwdemo_roll:18"] = "rtwdemo_roll.c:73";
	/* <S3>/LoThr */
	this.urlHashMap["rtwdemo_roll:25"] = "rtwdemo_roll.c:52";
	/* <S3>/NotEngaged */
	this.urlHashMap["rtwdemo_roll:20"] = "rtwdemo_roll.c:48";
	/* <S3>/Or */
	this.urlHashMap["rtwdemo_roll:26"] = "rtwdemo_roll.c:56";
	/* <S3>/RefSwitch */
	this.urlHashMap["rtwdemo_roll:27"] = "rtwdemo_roll.c:51,66";
	/* <S3>/RefThreshold1 */
	this.urlHashMap["rtwdemo_roll:21"] = "rtwdemo_roll.c:57";
	/* <S3>/RefThreshold2 */
	this.urlHashMap["rtwdemo_roll:22"] = "rtwdemo_roll.c:58";
	/* <S3>/TKSwitch */
	this.urlHashMap["rtwdemo_roll:24"] = "rtwdemo_roll.c:84";
	/* <S3>/TKThreshold */
	this.urlHashMap["rtwdemo_roll:23"] = "rtwdemo_roll.c:82";
	/* <S3>/Three */
	this.urlHashMap["rtwdemo_roll:29"] = "rtwdemo_roll.c:74";
	/* <S3>/UpThr */
	this.urlHashMap["rtwdemo_roll:28"] = "rtwdemo_roll.c:53";
	/* <S3>/Zero */
	this.urlHashMap["rtwdemo_roll:30"] = "rtwdemo_roll.c:54";
	/* <S7>/Enable */
	this.urlHashMap["rtwdemo_roll:19:3"] = "rtwdemo_roll.c:46,69";
	/* <S7>/FixPt
Data Type
Duplicate1 */
	this.urlHashMap["rtwdemo_roll:19:4"] = "msg=rtwMsg_SimulationReducedBlock&block=rtwdemo_roll/RollAngleReference/LatchPhi/FixPt%20Data%20Type%20Duplicate1";
	/* <S7>/FixPt
Unit Delay1 */
	this.urlHashMap["rtwdemo_roll:19:5"] = "rtwdemo_roll.c:43&rtwdemo_roll.h:41";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "rtwdemo_roll"};
	this.sidHashMap["rtwdemo_roll"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "rtwdemo_roll:74"};
	this.sidHashMap["rtwdemo_roll:74"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "rtwdemo_roll:52"};
	this.sidHashMap["rtwdemo_roll:52"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "rtwdemo_roll:14"};
	this.sidHashMap["rtwdemo_roll:14"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S4>"] = {sid: "rtwdemo_roll:37"};
	this.sidHashMap["rtwdemo_roll:37"] = {rtwname: "<S4>"};
	this.rtwnameHashMap["<S5>"] = {sid: "rtwdemo_roll:92"};
	this.sidHashMap["rtwdemo_roll:92"] = {rtwname: "<S5>"};
	this.rtwnameHashMap["<S6>"] = {sid: "rtwdemo_roll:59"};
	this.sidHashMap["rtwdemo_roll:59"] = {rtwname: "<S6>"};
	this.rtwnameHashMap["<S7>"] = {sid: "rtwdemo_roll:19"};
	this.sidHashMap["rtwdemo_roll:19"] = {rtwname: "<S7>"};
	this.rtwnameHashMap["<S8>"] = {sid: "rtwdemo_roll:38"};
	this.sidHashMap["rtwdemo_roll:38"] = {rtwname: "<S8>"};
	this.rtwnameHashMap["<Root>/Phi"] = {sid: "rtwdemo_roll:1"};
	this.sidHashMap["rtwdemo_roll:1"] = {rtwname: "<Root>/Phi"};
	this.rtwnameHashMap["<Root>/Psi"] = {sid: "rtwdemo_roll:2"};
	this.sidHashMap["rtwdemo_roll:2"] = {rtwname: "<Root>/Psi"};
	this.rtwnameHashMap["<Root>/P"] = {sid: "rtwdemo_roll:3"};
	this.sidHashMap["rtwdemo_roll:3"] = {rtwname: "<Root>/P"};
	this.rtwnameHashMap["<Root>/TAS"] = {sid: "rtwdemo_roll:4"};
	this.sidHashMap["rtwdemo_roll:4"] = {rtwname: "<Root>/TAS"};
	this.rtwnameHashMap["<Root>/AP_Eng"] = {sid: "rtwdemo_roll:5"};
	this.sidHashMap["rtwdemo_roll:5"] = {rtwname: "<Root>/AP_Eng"};
	this.rtwnameHashMap["<Root>/HDG_Mode"] = {sid: "rtwdemo_roll:6"};
	this.sidHashMap["rtwdemo_roll:6"] = {rtwname: "<Root>/HDG_Mode"};
	this.rtwnameHashMap["<Root>/HDG_Ref"] = {sid: "rtwdemo_roll:7"};
	this.sidHashMap["rtwdemo_roll:7"] = {rtwname: "<Root>/HDG_Ref"};
	this.rtwnameHashMap["<Root>/Turn_Knob"] = {sid: "rtwdemo_roll:8"};
	this.sidHashMap["rtwdemo_roll:8"] = {rtwname: "<Root>/Turn_Knob"};
	this.rtwnameHashMap["<Root>/BasicRollMode"] = {sid: "rtwdemo_roll:74"};
	this.sidHashMap["rtwdemo_roll:74"] = {rtwname: "<Root>/BasicRollMode"};
	this.rtwnameHashMap["<Root>/EngSwitch"] = {sid: "rtwdemo_roll:10"};
	this.sidHashMap["rtwdemo_roll:10"] = {rtwname: "<Root>/EngSwitch"};
	this.rtwnameHashMap["<Root>/HeadingMode"] = {sid: "rtwdemo_roll:52"};
	this.sidHashMap["rtwdemo_roll:52"] = {rtwname: "<Root>/HeadingMode"};
	this.rtwnameHashMap["<Root>/ModeSwitch"] = {sid: "rtwdemo_roll:12"};
	this.sidHashMap["rtwdemo_roll:12"] = {rtwname: "<Root>/ModeSwitch"};
	this.rtwnameHashMap["<Root>/RollAngleReference"] = {sid: "rtwdemo_roll:14"};
	this.sidHashMap["rtwdemo_roll:14"] = {rtwname: "<Root>/RollAngleReference"};
	this.rtwnameHashMap["<Root>/System I//O Specification"] = {sid: "rtwdemo_roll:37"};
	this.sidHashMap["rtwdemo_roll:37"] = {rtwname: "<Root>/System I//O Specification"};
	this.rtwnameHashMap["<Root>/Zero"] = {sid: "rtwdemo_roll:32"};
	this.sidHashMap["rtwdemo_roll:32"] = {rtwname: "<Root>/Zero"};
	this.rtwnameHashMap["<Root>/Ail_Cmd"] = {sid: "rtwdemo_roll:33"};
	this.sidHashMap["rtwdemo_roll:33"] = {rtwname: "<Root>/Ail_Cmd"};
	this.rtwnameHashMap["<S1>/Disp_Cmd"] = {sid: "rtwdemo_roll:77"};
	this.sidHashMap["rtwdemo_roll:77"] = {rtwname: "<S1>/Disp_Cmd"};
	this.rtwnameHashMap["<S1>/Disp_FB"] = {sid: "rtwdemo_roll:78"};
	this.sidHashMap["rtwdemo_roll:78"] = {rtwname: "<S1>/Disp_FB"};
	this.rtwnameHashMap["<S1>/Rate_FB"] = {sid: "rtwdemo_roll:79"};
	this.sidHashMap["rtwdemo_roll:79"] = {rtwname: "<S1>/Rate_FB"};
	this.rtwnameHashMap["<S1>/Engaged"] = {sid: "rtwdemo_roll:80"};
	this.sidHashMap["rtwdemo_roll:80"] = {rtwname: "<S1>/Engaged"};
	this.rtwnameHashMap["<S1>/CmdLimit"] = {sid: "rtwdemo_roll:81"};
	this.sidHashMap["rtwdemo_roll:81"] = {rtwname: "<S1>/CmdLimit"};
	this.rtwnameHashMap["<S1>/DispGain"] = {sid: "rtwdemo_roll:82"};
	this.sidHashMap["rtwdemo_roll:82"] = {rtwname: "<S1>/DispGain"};
	this.rtwnameHashMap["<S1>/DispLimit"] = {sid: "rtwdemo_roll:83"};
	this.sidHashMap["rtwdemo_roll:83"] = {rtwname: "<S1>/DispLimit"};
	this.rtwnameHashMap["<S1>/IntGain"] = {sid: "rtwdemo_roll:84"};
	this.sidHashMap["rtwdemo_roll:84"] = {rtwname: "<S1>/IntGain"};
	this.rtwnameHashMap["<S1>/Integrator"] = {sid: "rtwdemo_roll:85"};
	this.sidHashMap["rtwdemo_roll:85"] = {rtwname: "<S1>/Integrator"};
	this.rtwnameHashMap["<S1>/NotEngaged"] = {sid: "rtwdemo_roll:86"};
	this.sidHashMap["rtwdemo_roll:86"] = {rtwname: "<S1>/NotEngaged"};
	this.rtwnameHashMap["<S1>/RateGain"] = {sid: "rtwdemo_roll:87"};
	this.sidHashMap["rtwdemo_roll:87"] = {rtwname: "<S1>/RateGain"};
	this.rtwnameHashMap["<S1>/RateLimit"] = {sid: "rtwdemo_roll:88"};
	this.sidHashMap["rtwdemo_roll:88"] = {rtwname: "<S1>/RateLimit"};
	this.rtwnameHashMap["<S1>/Sum"] = {sid: "rtwdemo_roll:89"};
	this.sidHashMap["rtwdemo_roll:89"] = {rtwname: "<S1>/Sum"};
	this.rtwnameHashMap["<S1>/Sum1"] = {sid: "rtwdemo_roll:90"};
	this.sidHashMap["rtwdemo_roll:90"] = {rtwname: "<S1>/Sum1"};
	this.rtwnameHashMap["<S1>/Sum2"] = {sid: "rtwdemo_roll:91"};
	this.sidHashMap["rtwdemo_roll:91"] = {rtwname: "<S1>/Sum2"};
	this.rtwnameHashMap["<S1>/System I//O Specification"] = {sid: "rtwdemo_roll:92"};
	this.sidHashMap["rtwdemo_roll:92"] = {rtwname: "<S1>/System I//O Specification"};
	this.rtwnameHashMap["<S1>/Surf_Cmd"] = {sid: "rtwdemo_roll:93"};
	this.sidHashMap["rtwdemo_roll:93"] = {rtwname: "<S1>/Surf_Cmd"};
	this.rtwnameHashMap["<S2>/Psi_Ref"] = {sid: "rtwdemo_roll:53"};
	this.sidHashMap["rtwdemo_roll:53"] = {rtwname: "<S2>/Psi_Ref"};
	this.rtwnameHashMap["<S2>/Psi"] = {sid: "rtwdemo_roll:54"};
	this.sidHashMap["rtwdemo_roll:54"] = {rtwname: "<S2>/Psi"};
	this.rtwnameHashMap["<S2>/TAS"] = {sid: "rtwdemo_roll:55"};
	this.sidHashMap["rtwdemo_roll:55"] = {rtwname: "<S2>/TAS"};
	this.rtwnameHashMap["<S2>/DispGain"] = {sid: "rtwdemo_roll:56"};
	this.sidHashMap["rtwdemo_roll:56"] = {rtwname: "<S2>/DispGain"};
	this.rtwnameHashMap["<S2>/Product"] = {sid: "rtwdemo_roll:57"};
	this.sidHashMap["rtwdemo_roll:57"] = {rtwname: "<S2>/Product"};
	this.rtwnameHashMap["<S2>/Sum"] = {sid: "rtwdemo_roll:58"};
	this.sidHashMap["rtwdemo_roll:58"] = {rtwname: "<S2>/Sum"};
	this.rtwnameHashMap["<S2>/System I//O Specification"] = {sid: "rtwdemo_roll:59"};
	this.sidHashMap["rtwdemo_roll:59"] = {rtwname: "<S2>/System I//O Specification"};
	this.rtwnameHashMap["<S2>/Phi_Cmd"] = {sid: "rtwdemo_roll:60"};
	this.sidHashMap["rtwdemo_roll:60"] = {rtwname: "<S2>/Phi_Cmd"};
	this.rtwnameHashMap["<S3>/Phi"] = {sid: "rtwdemo_roll:15"};
	this.sidHashMap["rtwdemo_roll:15"] = {rtwname: "<S3>/Phi"};
	this.rtwnameHashMap["<S3>/AP_Eng"] = {sid: "rtwdemo_roll:16"};
	this.sidHashMap["rtwdemo_roll:16"] = {rtwname: "<S3>/AP_Eng"};
	this.rtwnameHashMap["<S3>/Turn_Knob"] = {sid: "rtwdemo_roll:17"};
	this.sidHashMap["rtwdemo_roll:17"] = {rtwname: "<S3>/Turn_Knob"};
	this.rtwnameHashMap["<S3>/Abs"] = {sid: "rtwdemo_roll:18"};
	this.sidHashMap["rtwdemo_roll:18"] = {rtwname: "<S3>/Abs"};
	this.rtwnameHashMap["<S3>/LatchPhi"] = {sid: "rtwdemo_roll:19"};
	this.sidHashMap["rtwdemo_roll:19"] = {rtwname: "<S3>/LatchPhi"};
	this.rtwnameHashMap["<S3>/LoThr"] = {sid: "rtwdemo_roll:25"};
	this.sidHashMap["rtwdemo_roll:25"] = {rtwname: "<S3>/LoThr"};
	this.rtwnameHashMap["<S3>/NotEngaged"] = {sid: "rtwdemo_roll:20"};
	this.sidHashMap["rtwdemo_roll:20"] = {rtwname: "<S3>/NotEngaged"};
	this.rtwnameHashMap["<S3>/Or"] = {sid: "rtwdemo_roll:26"};
	this.sidHashMap["rtwdemo_roll:26"] = {rtwname: "<S3>/Or"};
	this.rtwnameHashMap["<S3>/RefSwitch"] = {sid: "rtwdemo_roll:27"};
	this.sidHashMap["rtwdemo_roll:27"] = {rtwname: "<S3>/RefSwitch"};
	this.rtwnameHashMap["<S3>/RefThreshold1"] = {sid: "rtwdemo_roll:21"};
	this.sidHashMap["rtwdemo_roll:21"] = {rtwname: "<S3>/RefThreshold1"};
	this.rtwnameHashMap["<S3>/RefThreshold2"] = {sid: "rtwdemo_roll:22"};
	this.sidHashMap["rtwdemo_roll:22"] = {rtwname: "<S3>/RefThreshold2"};
	this.rtwnameHashMap["<S3>/System I//O Specification"] = {sid: "rtwdemo_roll:38"};
	this.sidHashMap["rtwdemo_roll:38"] = {rtwname: "<S3>/System I//O Specification"};
	this.rtwnameHashMap["<S3>/TKSwitch"] = {sid: "rtwdemo_roll:24"};
	this.sidHashMap["rtwdemo_roll:24"] = {rtwname: "<S3>/TKSwitch"};
	this.rtwnameHashMap["<S3>/TKThreshold"] = {sid: "rtwdemo_roll:23"};
	this.sidHashMap["rtwdemo_roll:23"] = {rtwname: "<S3>/TKThreshold"};
	this.rtwnameHashMap["<S3>/Three"] = {sid: "rtwdemo_roll:29"};
	this.sidHashMap["rtwdemo_roll:29"] = {rtwname: "<S3>/Three"};
	this.rtwnameHashMap["<S3>/UpThr"] = {sid: "rtwdemo_roll:28"};
	this.sidHashMap["rtwdemo_roll:28"] = {rtwname: "<S3>/UpThr"};
	this.rtwnameHashMap["<S3>/Zero"] = {sid: "rtwdemo_roll:30"};
	this.sidHashMap["rtwdemo_roll:30"] = {rtwname: "<S3>/Zero"};
	this.rtwnameHashMap["<S3>/Phi_Ref"] = {sid: "rtwdemo_roll:31"};
	this.sidHashMap["rtwdemo_roll:31"] = {rtwname: "<S3>/Phi_Ref"};
	this.rtwnameHashMap["<S4>/EmptySubsystem"] = {sid: "rtwdemo_roll:37:134"};
	this.sidHashMap["rtwdemo_roll:37:134"] = {rtwname: "<S4>/EmptySubsystem"};
	this.rtwnameHashMap["<S5>/EmptySubsystem"] = {sid: "rtwdemo_roll:92:134"};
	this.sidHashMap["rtwdemo_roll:92:134"] = {rtwname: "<S5>/EmptySubsystem"};
	this.rtwnameHashMap["<S6>/EmptySubsystem"] = {sid: "rtwdemo_roll:59:134"};
	this.sidHashMap["rtwdemo_roll:59:134"] = {rtwname: "<S6>/EmptySubsystem"};
	this.rtwnameHashMap["<S7>/u"] = {sid: "rtwdemo_roll:19:1"};
	this.sidHashMap["rtwdemo_roll:19:1"] = {rtwname: "<S7>/u"};
	this.rtwnameHashMap["<S7>/E"] = {sid: "rtwdemo_roll:19:2"};
	this.sidHashMap["rtwdemo_roll:19:2"] = {rtwname: "<S7>/E"};
	this.rtwnameHashMap["<S7>/Enable"] = {sid: "rtwdemo_roll:19:3"};
	this.sidHashMap["rtwdemo_roll:19:3"] = {rtwname: "<S7>/Enable"};
	this.rtwnameHashMap["<S7>/FixPt Data Type Duplicate1"] = {sid: "rtwdemo_roll:19:4"};
	this.sidHashMap["rtwdemo_roll:19:4"] = {rtwname: "<S7>/FixPt Data Type Duplicate1"};
	this.rtwnameHashMap["<S7>/FixPt Unit Delay1"] = {sid: "rtwdemo_roll:19:5"};
	this.sidHashMap["rtwdemo_roll:19:5"] = {rtwname: "<S7>/FixPt Unit Delay1"};
	this.rtwnameHashMap["<S7>/y"] = {sid: "rtwdemo_roll:19:6"};
	this.sidHashMap["rtwdemo_roll:19:6"] = {rtwname: "<S7>/y"};
	this.rtwnameHashMap["<S8>/EmptySubsystem"] = {sid: "rtwdemo_roll:38:134"};
	this.sidHashMap["rtwdemo_roll:38:134"] = {rtwname: "<S8>/EmptySubsystem"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
