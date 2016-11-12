object frmsalebsset: Tfrmsalebsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #25209#38144#19994#21153#25511#21046
  ClientHeight = 419
  ClientWidth = 664
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 17
  object sbcancel: TSpeedButton
    Left = 539
    Top = 380
    Width = 105
    Height = 33
    Caption = #21462#28040
    OnClick = sbcancelClick
  end
  object sbok: TSpeedButton
    Left = 435
    Top = 378
    Width = 98
    Height = 33
    Caption = #30830#23450
    OnClick = sbokClick
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 223
    Width = 651
    Height = 154
    Caption = #25209#38144#25240#25187#35774#32622
    TabOrder = 0
    object Label3: TLabel
      Left = 585
      Top = 52
      Width = 11
      Height = 17
      Caption = '%'
    end
    object Label10: TLabel
      Left = 154
      Top = -62
      Width = 156
      Height = 68
      Caption = #27880#65306#22312#25240#25187#35774#32622#20013#65292#25209#38144#36319#36394#13#19978#27425#25240#25187#21644#25209#38144#40664#35748#25240#25187#24517#39035#13#26377#25928#25165#33021#22312#20248#20808#32423#21035#21644#26368#20302#25240#13#25187#20013#29983#25928
      Visible = False
    end
    object Label4: TLabel
      Left = 24
      Top = 83
      Width = 84
      Height = 17
      Caption = #35831#36873#25321#25171#25240#39034#24207
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 262
      Top = 83
      Width = 17
      Height = 17
      Caption = '-'#12299
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 416
      Top = 83
      Width = 17
      Height = 17
      Caption = '-'#12299
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 108
      Top = 119
      Width = 17
      Height = 17
      Caption = '-'#12299
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 262
      Top = 119
      Width = 17
      Height = 17
      Caption = '-'#12299
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 416
      Top = 119
      Width = 17
      Height = 17
      Caption = '-'#12299
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object RadioGroup1: TRadioGroup
      Left = 89
      Top = -15
      Width = 273
      Height = 33
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        #20248#20808#32423#21035#35774#32622
        #26368#20302#25240#25187)
      TabOrder = 0
      Visible = False
    end
    object cbpxdefaultdiscount: TCheckBox
      Left = 439
      Top = 53
      Width = 92
      Height = 17
      Caption = #25209#38144#40664#35748#25240#25187
      TabOrder = 1
    end
    object chpxlastdiscount: TCheckBox
      Left = 25
      Top = 52
      Width = 145
      Height = 17
      Caption = #25209#38144#36319#36394#19978#27425#25240#25187#21551#29992
      TabOrder = 2
    end
    object cbwsaledisscountchange: TCheckBox
      Left = 233
      Top = 52
      Width = 146
      Height = 17
      Caption = #20801#35768#20462#25913#25240#25187#30340#35774#32622
      TabOrder = 3
    end
    object eddefaultdiscount: TEdit
      Left = 532
      Top = 49
      Width = 49
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 4
      Text = '100'
      OnKeyPress = eddefaultdiscountKeyPress
    end
    object cb1: TComboBox
      Left = 127
      Top = 80
      Width = 129
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 5
    end
    object cb2: TComboBox
      Left = 281
      Top = 80
      Width = 129
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 6
    end
    object cb3: TComboBox
      Left = 434
      Top = 80
      Width = 129
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 7
    end
    object cb4: TComboBox
      Left = 127
      Top = 116
      Width = 129
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 8
    end
    object cb5: TComboBox
      Left = 281
      Top = 116
      Width = 129
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 9
    end
    object chpxclientadddot: TCheckBox
      Left = 25
      Top = 26
      Width = 129
      Height = 17
      Caption = #23458#25143#21152#28857#25240#25187#21551#29992
      TabOrder = 10
    end
    object chpxrkyjdiscount: TCheckBox
      Left = 233
      Top = 26
      Width = 146
      Height = 17
      Caption = #20837#24211#39044#35745#25209#38144#25240#25187#21551#29992
      TabOrder = 11
    end
    object chpxaddcost: TCheckBox
      Left = 439
      Top = 26
      Width = 146
      Height = 17
      Caption = #38468#21152#25240#25187#21551#29992
      TabOrder = 12
    end
    object cb6: TComboBox
      Left = 434
      Top = 116
      Width = 129
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 13
    end
  end
  object 销售业务: TGroupBox
    Left = 6
    Top = 5
    Width = 651
    Height = 212
    TabOrder = 1
    object Label23: TLabel
      Left = 439
      Top = 67
      Width = 96
      Height = 17
      Caption = #25209#38144#26126#32454#35760#24405#22825#25968
    end
    object Label1: TLabel
      Left = 232
      Top = 38
      Width = 60
      Height = 17
      Caption = #23567#25968#28857#20301#25968
    end
    object Label2: TLabel
      Left = 340
      Top = 38
      Width = 91
      Height = 17
      Caption = #65288#26368#22810#35774#32622'2'#20301#65289
    end
    object Label11: TLabel
      Left = 24
      Top = 181
      Width = 132
      Height = 17
      Caption = #26412#26399#25209#38144#36864#36135#29575#35745#31639#26102#38388
    end
    object Label12: TLabel
      Left = 205
      Top = 181
      Width = 12
      Height = 17
      Caption = #26376
    end
    object cbbear: TCheckBox
      Left = 24
      Top = 38
      Width = 145
      Height = 17
      Caption = #20801#35768#36127#24211#23384#38144#21806
      TabOrder = 0
    end
    object cbwosalehistory: TCheckBox
      Left = 24
      Top = 66
      Width = 154
      Height = 17
      Caption = #26174#31034#21382#21490#25209#38144#26126#32454
      TabOrder = 1
    end
    object edwosaleday: TEdit
      Left = 545
      Top = 63
      Width = 49
      Height = 23
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 2
    end
    object cbcheckedview: TCheckBox
      Left = 485
      Top = 23
      Width = 193
      Height = 17
      Caption = #26174#31034#24403#21069#23458#25143#32467'/'#27424#27454#24773#20917
      TabOrder = 3
      Visible = False
    end
    object cbwosalereturn: TCheckBox
      Left = 464
      Top = 0
      Width = 146
      Height = 17
      Caption = #20801#35768#26080#25209#38144#36864#36135
      TabOrder = 4
      Visible = False
    end
    object cblowcostalter: TCheckBox
      Left = 24
      Top = 95
      Width = 129
      Height = 17
      Caption = #20302#20110#25104#26412#25240#25187#25552#37266
      TabOrder = 5
    end
    object cblownormalalter: TCheckBox
      Left = 24
      Top = 124
      Width = 119
      Height = 17
      Caption = #20302#20110#27491#24120#25240#25187#25552#37266
      TabOrder = 6
    end
    object cblownormalenable: TCheckBox
      Left = 232
      Top = 124
      Width = 146
      Height = 17
      Caption = #20302#20110#27491#24120#25240#25187#21457#36135
      TabOrder = 7
    end
    object cblowcostenable: TCheckBox
      Left = 232
      Top = 95
      Width = 146
      Height = 17
      Caption = #20302#20110#25104#26412#25240#25187#21457#36135
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 8
    end
    object etdot: TEdit
      Left = 310
      Top = 34
      Width = 35
      Height = 23
      Ctl3D = False
      MaxLength = 1
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 9
      OnExit = etdotExit
    end
    object cbpxtuihuocatch: TCheckBox
      Left = 24
      Top = 11
      Width = 97
      Height = 17
      Caption = #36864#36135#30417#31649
      TabOrder = 10
      OnClick = cbpxtuihuocatchClick
    end
    object chxianchangrecive: TCheckBox
      Left = 232
      Top = 11
      Width = 169
      Height = 17
      Caption = #25209#38144#30028#38754#29616#22330#25910#27454#21487#29992
      TabOrder = 11
    end
    object cbpxallclientdetail: TCheckBox
      Left = 232
      Top = 66
      Width = 199
      Height = 17
      Caption = #25209#38144#26126#32454#26174#31034#25152#26377#23458#25143#21382#21490#35760#24405
      TabOrder = 12
    end
    object cbpxdeleteusepassword: TCheckBox
      Left = 232
      Top = 155
      Width = 145
      Height = 17
      Caption = #21551#29992#25209#38144#21024#21333#23494#30721
      TabOrder = 13
    end
    object cbpxnobkinfosale: TCheckBox
      Left = 398
      Top = 294
      Width = 97
      Height = 17
      Caption = #26080#24211#23384#25209#38144
      TabOrder = 14
      Visible = False
    end
    object cbpxnobkinfotuihuo: TCheckBox
      Left = 533
      Top = 294
      Width = 130
      Height = 17
      Caption = #26080#24211#23384#25209#38144#36864#36135
      TabOrder = 15
      Visible = False
    end
    object cbpxfindusepassword: TCheckBox
      Left = 438
      Top = 124
      Width = 154
      Height = 17
      Caption = #21551#29992#25209#38144#26597#21333#23494#30721
      TabOrder = 16
    end
    object cbpxtuihuousepassword: TCheckBox
      Left = 438
      Top = 95
      Width = 186
      Height = 17
      Caption = #21551#29992#25209#38144#36864#36135#23494#30721
      TabOrder = 17
    end
    object chnokucunpxth: TCheckBox
      Left = 23
      Top = 155
      Width = 154
      Height = 17
      Caption = #20801#35768#26080#24211#23384#25209#38144#36864#36135
      TabOrder = 18
    end
    object edmonth: TEdit
      Left = 164
      Top = 178
      Width = 37
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 19
      Text = '3'
    end
    object chpxusechange: TCheckBox
      Left = 439
      Top = 155
      Width = 193
      Height = 17
      Caption = #21551#29992#25209#38144#20462#25913#21333#22836#23494#30721
      TabOrder = 20
    end
    object chwsalesametishi: TCheckBox
      Left = 232
      Top = 180
      Width = 129
      Height = 17
      Caption = #20801#35768#25209#38144#37325#22797#24405#20837
      TabOrder = 21
    end
    object cbpxtuihuo: TCheckBox
      Left = 439
      Top = 178
      Width = 141
      Height = 17
      Caption = #20801#35768#25209#38144#36864#36135#37325#22797#24405#20837
      TabOrder = 22
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 424
    Top = 504
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 600
    Top = 128
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 384
    Top = 248
  end
end
