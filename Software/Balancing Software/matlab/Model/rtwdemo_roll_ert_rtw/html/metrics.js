function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtwdemo_roll_DW"] = {file: "C:\\Users\\Panoply\\Documents\\bot\\Software\\Balancing Software\\matlab\\Model\\rtwdemo_roll_ert_rtw\\rtwdemo_roll.c",
	size: 9};
	 this.metricsArray.var["rtwdemo_roll_M_"] = {file: "C:\\Users\\Panoply\\Documents\\bot\\Software\\Balancing Software\\matlab\\Model\\rtwdemo_roll_ert_rtw\\rtwdemo_roll.c",
	size: 4};
	 this.metricsArray.var["rtwdemo_roll_U"] = {file: "C:\\Users\\Panoply\\Documents\\bot\\Software\\Balancing Software\\matlab\\Model\\rtwdemo_roll_ert_rtw\\rtwdemo_roll.c",
	size: 26};
	 this.metricsArray.var["rtwdemo_roll_Y"] = {file: "C:\\Users\\Panoply\\Documents\\bot\\Software\\Balancing Software\\matlab\\Model\\rtwdemo_roll_ert_rtw\\rtwdemo_roll.c",
	size: 4};
	 this.metricsArray.fcn["fabs"] = {file: "C:\\Program Files\\MATLAB\\MATLAB Production Server\\R2015a\\sys\\lcc\\include\\math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtwdemo_roll_initialize"] = {file: "C:\\Users\\Panoply\\Documents\\bot\\Software\\Balancing Software\\matlab\\Model\\rtwdemo_roll_ert_rtw\\rtwdemo_roll.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtwdemo_roll_step"] = {file: "C:\\Users\\Panoply\\Documents\\bot\\Software\\Balancing Software\\matlab\\Model\\rtwdemo_roll_ert_rtw\\rtwdemo_roll.c",
	stack: 5,
	stackTotal: 5};
	 this.metricsArray.fcn["rtwdemo_roll_terminate"] = {file: "C:\\Users\\Panoply\\Documents\\bot\\Software\\Balancing Software\\matlab\\Model\\rtwdemo_roll_ert_rtw\\rtwdemo_roll.c",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data;}
}
	 CodeMetrics.instance = new CodeMetrics();
