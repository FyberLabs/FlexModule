****************************************************************************
*
* WARNING : please consider following remarks before usage
*
* 1) All models are a tradeoff between accuracy and complexity (ie. simulation
*    time).
*
* 2) Macromodels are not a substitute to breadboarding, they rather confirm the
*    validity of a design approach and help to select surrounding component values.
*
* 3) A macromodel emulates the NOMINAL performance of a TYPICAL device within
*    SPECIFIED OPERATING CONDITIONS (ie. temperature, supply voltage, etc.).
*    Thus the macromodel is often not as exhaustive as the datasheet, its goal
*    is to illustrate the main parameters of the product.
*
* 4) Data issued from macromodels used outside of its specified conditions
*    (Vcc, Temperature, etc) or even worse: outside of the device operating
*    conditions (Vcc, Vicm, etc) are not reliable in any way.
*
****************************************************************************
****
***  TSZ121 Spice macromodel subckt 
***
***      September 2013
****                      
************ CONNECTIONS: 
****               NON-INVERTING INPUT
****                 |  INVERTING INPUT
****                 |   |     POSITIVE POWER SUPPLY
****                 |   |       |     NEGATIVE POWER SUPPLY
****                 |   |       |      |      OUTPUT  
****                 |   |       |      |       |     
****                 |   |       |      |       |    
.SUBCKT TSZ121 VP VM   VCCP VCCN  VS
    LOUT VZOUT 0 {LOUT}
    FIOUT 0 VZOUT VREADIO 1.0
    M_NMOS2 VO_DIFF_MINUS VM VEE_N VCCN_ENHANCED MOS_N L={L} W={W}
    M_NMOS1 VO_DIFF_PLUS NET194 VEE_N VCCN_ENHANCED MOS_N L={L} W={W}
    IEE_N VEE_N VCCN_ENHANCED DC {IEE}
    VVLIM_LOW_VB NET192 NET193 DC -770m
    VOS NET194 VP DC 0
    VPROT_IN_P_VCCP NET196 NET229 DC {V_DPROT}
    V_ENHANCE_VCCN VCCN_ENHANCED VCCN DC {VCCN_ENHANCE}
    VREADIO NET0313 VS DC 0
    VVLIM_HIGH_VB NET217 NET203 DC -770m
    V_ENHANCE_VCCP VCCP_ENHANCED VCCP DC {VCCP_ENHANCE}
    V_OUTVLIM_LOW NET206 NET207 DC {VD_COMPENSAZIONE}
    VPROT_IN_M_VCCN NET208 NET360 DC {V_DPROT}
    V_OUTVLIM_HIGH NET235 NET211 DC {VD_COMPENSAZIONE}
    VPROT_IN_P_VCCN NET212 NET213 DC {V_DPROT}
    VPROT_IN_M_VCCP NET348 NET219 DC {V_DPROT}
    DVLIM_HIGH_VB VB NET217 DIODE_VLIM
    DPROT_IN_M_VCCP VM NET219 DIODE_VLIM
    DVLIM_LOW_VB NET193 VB DIODE_VLIM
    DPROT_IN_M_VCCN NET208 VM DIODE_VLIM
    DILIM_SINK VB_3_SINK VB_3 DIODE_ILIM
    D_OUTVLIM_LOW NET207 VB_3 DIODE_NOVd
    DPROT_IN_P_VCCP NET194 NET229 DIODE_VLIM
    DILIM_SOURCE VB_3 VB_3_SOURCE DIODE_ILIM
    DPROT_IN_P_VCCN NET212 NET194 DIODE_VLIM
    D_OUTVLIM_HIGH VB_3 NET235 DIODE_NOVd
    CZOUT_IOUT_COEFF VZOUT_IOUT_COEFF 0 1n
    COUT2 VZOUT 0 {COUT2}
    CIN_CM_VM VM VREF {CIN_CM_VM}
    CIN_CM_VP VP VREF {CIN_CM_VP}
    CIN_DIFF VM VP {CIN_DIFF}
    C_RO2_1 VB_2 VREF 1.2n
    COUT NET0410 0 {COUT}
    CDIFF_PARASITIC VO_DIFF_PLUS VO_DIFF_MINUS 2p
    CCOMP VB VB_2 {CCOMP}
    EZOUT_VCC_COEFF VZOUT_VCC_COEFF 0 POLY(1) VCCP VCCN 1.8362728537360917
+-0.4613119971575888 0.0846310883075601 -0.0051639206050971935
    EZOUT_IOUT_COEFF NET0295 0 VALUE={IF( I(VreadIo)>=0 , (
+Zout_Iout_coeff_MIN + (1.0 -
+Zout_Iout_coeff_MIN)*exp(-abs(I(VreadIo)/Iout_dc_tau__source)) ) , (
+Zout_Iout_coeff_MIN + (1.0 -
+Zout_Iout_coeff_MIN)*exp(-abs(I(VreadIo)/Iout_dc_tau__sink)) ) )}
    EZOUT VB_3 NET0313
+VALUE={V(VZout)*V(VZout_Iout_coeff)*V(VZout_Vcc_coeff)}
    E_SR_VCC_MODULATION VOUT_DIFF__SR_VCC 0 VALUE={V(Vout_diff)*(
+0.27501150296278326 + 0.8286956472979377*V(Vccp,Vccn)
+-0.3769832162624067*PWR(V(Vccp,Vccn),2) +
+0.0852740909465122*PWR(V(Vccp,Vccn),3)
+-0.009588582374966497*PWR(V(Vccp,Vccn),4) +
+(4.2870011729922677E-4)*PWR(V(Vccp,Vccn),5) )}
    E_ICCSAT_HIGH ICC_OUT_HIGH 0 VALUE={0}
    E_RO1_VOL RO1_VOL 0 POLY(1) VCCP VCCN 62.47426470588232
+-4.104166666666657 0.28186274509803794
    E_ICCSAT_LOW ICC_OUT_LOW 0 VALUE={0}
    E_READIO V_IO_VAL 0 VALUE={I(VreadIo)}
    E58 VB_2_VREF 0 VB_2 VREF 1.0
    EILIM_SINK VB_3_SINK VDEP_SINK VB_3 0 1.0
    E_RO1_VOH RO1_VOH 0 POLY(1) VCCP VCCN 89.69852941176467 -15.125
+1.3970588235294117
    EMEAS_VB_VREF VB_VREF 0 VB VREF 1.0
    EMEAS_VOUT_DIFF VOUT_DIFF 0 VO_DIFF_PLUS VO_DIFF_MINUS 1.0
    E_VDEP_SOURCE_2 VAL_VDEP_SOURCE_FILTERED 0
+VALUE={IF(V(val_vdep_source)>=0, 0, V(val_vdep_source))}
    E_VDEP_SINK_1 VAL_VDEP_SINK 0 VALUE={ ( 357.60726351349297
+-412.65484234231866*V(Vccp,Vccn) + 140.89480105104104*PWR(V(Vccp,Vccn),2)
+ -21.11486486486304*PWR(V(Vccp,Vccn),3) +
+1.1730480480479284*PWR(V(Vccp,Vccn),4) )  -5000*I(VreadIo)}
    EVLIM_HIGH_VOUT NET211 0 VALUE={V(VCCP) - V(Ro1_Voh)*I(VreadIo)}
    EVLIM_LOW_VOUT NET206 0 VALUE={V(VCCN) - V(Ro1_Vol)*I(VreadIo) +
+V(VOL_noRL) }
    E_VDEP_SOURCE_3 VDEP_SOURCE 0 VALUE={IF( V(Vccp,Vccn)<VCC_MIN , 0 ,
+V(val_vdep_source_filtered))}
    EVLIM_HIGH_VB NET203 0 VCCP 0 1.0
    E_VDEP_SINK_2 VAL_VDEP_SINK_FILTERED 0
+VALUE={IF(V(val_vdep_sink)<=0 , 0 , V(val_vdep_sink))}
    EVLIM_LOW_VB NET192 0 VCCN 0 1.0
    E2_REF NET362 0 VCCN 0 1.0
    E_VREF VREF 0 NET356 0 1.0
    E_VOL_NORL VOL_NORL 0 VALUE={0}
    E_VDEP_SINK_3 VDEP_SINK 0 VALUE={IF( V(Vccp,Vccn)<VCC_MIN , 0 ,
+V(val_vdep_sink_filtered))}
    E1_REF NET326 0 VCCP 0 1.0
    E_VDEP_SOURCE_1 VAL_VDEP_SOURCE 0 VALUE={ ( -254.01148801515134 +
+290.6577969371937*V(Vccp,Vccn) -94.89295715398025*PWR(V(Vccp,Vccn),2)  +
+13.840310899133279*PWR(V(Vccp,Vccn),3) 
+-0.7559878883407544*PWR(V(Vccp,Vccn),4) )  -5000*I(VreadIo)}
    EILIM_SOURCE VB_3_SOURCE VDEP_SOURCE VB_3 0 1.0
    R1 VB VREF {R1}
    RZOUT_IOUT_COEFF VZOUT_IOUT_COEFF NET0295 50
    RIN_CM_VP VREF VP {RIN_CM_VP}
    RIN_DIFF VP VM {RIN_DIFF}
    ROUT NET0410 VZOUT {ROUT}
    R_ICCSAT_LOW ICC_OUT_LOW 0 1K
    RO2_2 VB_3 VB_2 {RO2_2}
    RPROT_IN_P_VCCP NET196 VCCP 100
    RPROT_IN_M_VCCP VCCP NET348 100
    RO2_1 VB_2 VREF {RO2_1}
    RD1 VCCP_ENHANCED VO_DIFF_PLUS {RD}
    RD2 VCCP_ENHANCED VO_DIFF_MINUS {RD}
    RIN_CM_VM VREF VM {RIN_CM_VM}
    R1_REF NET326 NET356 1Meg
    R_ICCSAT_HIGH ICC_OUT_HIGH 0 1K
    RPROT_IN_M_VCCN VCCN NET360 15K
    R2_REF NET356 NET362 1Meg
    RPROT_IN_P_VCCN NET213 VCCN 15K
    G_ICCSAT_OUTLOW VCCP VCCN VALUE={IF(I(V_OUTVLIM_LOW)>1u ,
+V(Icc_out_low) , 0)}
    G_I_VB VB_2 VREF VB_VREF 0 {GB}
    G_I_IO VB_2 VREF VALUE={V(VB_Vref)*GB*( 10*( 1 -
+exp(-abs(V(v_Io_val))/0.2m )) )  }
    G_IOUT_SOURCED VCCP 0 VALUE={IF(I(VreadIo)>0, I(VreadIo),0)}
    GM1 VREF VB VOUT_DIFF__SR_VCC 0 {1/RD}
    G_IIB_VM VREF VM POLY(1) VCCP VCCN 3.654411764705885E-11
+7.91666666666665E-12 -2.450980392156842E-13
    G_ICC VCCP VCCN POLY(1) VCCP VCCN 2.5746323529411758E-5
+-1.458333333333355E-7 1.5931372549019658E-7
    G_ICCSAT_OUTHIGH VCCP VCCN VALUE={IF(I(V_OUTVLIM_HIGH)>1u ,
+V(Icc_out_high), 0)}
    G_IIB_VP VREF VP POLY(1) VCCP VCCN 3.654411764705885E-11
+7.91666666666665E-12 -2.450980392156842E-13
    G_IOUT_SINKED VCCN 0 VALUE={IF(I(VreadIo)>0, 0, I(VreadIo))}
    
    
*******************************************************************************
*
* MODELS/SUBCKTS and PARAMS used by TSZ121 subckt:
*
.PARAM VCC_MIN=1.5
.PARAM RINCM=4.9961E+10
.PARAM CINCM=1.2533E-11  
.PARAM RIN_CM_VM={2*RINCM}
.PARAM RIN_CM_VP={2*RINCM}
.PARAM CIN_CM_VM={CINCM/2}
.PARAM CIN_CM_VP={CINCM/2}
.PARAM RINDIFF=1.8019E+09
.PARAM CINDIFF=7.5304E-12
.PARAM RIN_DIFF={(2*RINCM*RINDIFF)/(2*RINCM - RINDIFF)}  
.PARAM CIN_DIFF={CINDIFF - CINCM/2}
.PARAM RD=1k
.PARAM VCCP_enhance=150m
.PARAM VCCN_enhance=-1100m 
.PARAM GB=10m
.PARAM Ro = 1.1229E+05
.PARAM A0=1e+7
.PARAM Ccomp=10.04p 
.PARAM IEE=2u
.PARAM W=0.81u
.PARAM L=1u
.PARAM gm_mos=2.8481E-05
.PARAM Lout  = 10m
.PARAM Rout  = 1300
.PARAM Cout  = 20n
.PARAM Cout2 = 0.7p
.PARAM Zout_Iout_coeff_MIN= 1.0
.PARAM Iout_dc_tau__source = 0.3m 
.PARAM Iout_dc_tau__sink   = 0.3m 
.PARAM Ro2_2=1e-3 
.PARAM Ro2_1={ Ro - Ro2_2} 
.PARAM R1={A0/(gm_mos*GB*Ro2_1)}
.PARAM V_DPROT=150m
.PARAM Vd_compensazione=-788.4u

.MODEL MOS_N  NMOS LEVEL=1  VTO=+0.65  KP=500E-6 
.MODEL DIODE_NOVd D LEVEL=1  IS=10E-15 N=0.001
.MODEL DIODE_VLIM D LEVEL=1  IS=0.8E-15   
.MODEL DIODE_ILIM D LEVEL=1  IS=0.8E-15  
*
*******************************************************************************

.ENDS TSZ121
*** End of subcircuit definition.





