object frmstoragebsset: Tfrmstoragebsset
  Left = 0
  Top = 0
  BiDiMode = bdLeftToRight
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #20837#24211#19994#21153#25511#21046
  ClientHeight = 529
  ClientWidth = 566
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 17
  object sbcancel: TSpeedButton
    Left = 454
    Top = 487
    Width = 89
    Height = 33
    Caption = #21462#28040
    OnClick = sbcancelClick
  end
  object sbok: TSpeedButton
    Left = 360
    Top = 487
    Width = 88
    Height = 33
    Caption = #30830#23450
    OnClick = sbokClick
  end
  object GroupBox1: TGroupBox
    Left = 4
    Top = 4
    Width = 557
    Height = 477
    BiDiMode = bdLeftToRight
    Color = clBtnFace
    Ctl3D = True
    ParentBackground = False
    ParentBiDiMode = False
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 0
    object Label1: TLabel
      Left = 319
      Top = 91
      Width = 60
      Height = 17
      Caption = #23567#25968#28857#20301#25968
    end
    object Label2: TLabel
      Left = 438
      Top = 91
      Width = 91
      Height = 17
      Caption = #65288#26368#22810#35774#32622'4'#20301#65289
    end
    object 进退货明细: TLabel
      Left = 320
      Top = 265
      Width = 113
      Height = 17
      Caption = #36827'/'#36864#36135#26126#32454#35760#24405#22825#25968
    end
    object Label3: TLabel
      Left = 25
      Top = 393
      Width = 132
      Height = 17
      Caption = #39044#35745#25209#38144#25240#25187#20197#20309#31181#20248#20808
    end
    object Label4: TLabel
      Left = 24
      Top = 91
      Width = 132
      Height = 17
      Caption = #26412#26399#20837#24211#36864#36135#29575#35745#31639#26102#38388
    end
    object Label5: TLabel
      Left = 222
      Top = 91
      Width = 12
      Height = 17
      Caption = #26376
    end
    object Label6: TLabel
      Left = 24
      Top = 120
      Width = 96
      Height = 17
      Caption = #20837#24211#36864#36135#40664#35748#21608#26399
    end
    object Label8: TLabel
      Left = 25
      Top = 445
      Width = 84
      Height = 17
      Caption = #22810#36135#28304#20986#24211#39034#24207
    end
    object sbsettuihuozhouqi: TSpeedButton
      Left = 278
      Top = 144
      Width = 59
      Height = 24
      Caption = #21608#26399#35774#32622
      OnClick = sbsettuihuozhouqiClick
    end
    object sbset: TSpeedButton
      Left = 222
      Top = 143
      Width = 49
      Height = 24
      Caption = #35774#32622
      OnClick = sbsetClick
    end
    object cbsameid: TCheckBox
      Left = 24
      Top = 13
      Width = 130
      Height = 17
      Caption = #20801#35768#20837#24211#37325#22797#24405#20837
      TabOrder = 0
    end
    object cborder: TCheckBox
      Left = 184
      Top = 36
      Width = 113
      Height = 17
      Caption = #26377#35746#36135#35760#24405#25552#31034
      TabOrder = 1
      Visible = False
    end
    object cbauto: TCheckBox
      Left = 24
      Top = 38
      Width = 154
      Height = 17
      Caption = #33258#21160#27880#38144#37319#36141#35760#24405
      TabOrder = 2
    end
    object cbtrace: TCheckBox
      Left = 24
      Top = 331
      Width = 129
      Height = 17
      Caption = #36319#36394#19978#27425#20837#24211#25240#25187
      TabOrder = 3
    end
    object etdot: TEdit
      Left = 397
      Top = 88
      Width = 35
      Height = 23
      Ctl3D = False
      MaxLength = 1
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 4
    end
    object cbstoragehistory: TCheckBox
      Left = 25
      Top = 265
      Width = 170
      Height = 17
      Caption = #26174#31034#21382#21490#36827'/'#36864#36135#26126#32454
      TabOrder = 5
    end
    object edstorageday: TEdit
      Left = 439
      Top = 262
      Width = 49
      Height = 23
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 6
    end
    object cbadddotenable: TCheckBox
      Left = 320
      Top = 335
      Width = 217
      Height = 17
      Caption = #39044#35745#25209#38144#25240#25187#26159#21542#21551#29992#38468#21152#28857#35774#32622
      TabOrder = 7
    end
    object cblastyjpxdiscount: TCheckBox
      Left = 25
      Top = 364
      Width = 145
      Height = 17
      Caption = #36319#36394#19978#27425#39044#35745#25209#38144#25240#25187
      TabOrder = 8
    end
    object cblastyjpx: TCheckBox
      Left = 239
      Top = 393
      Width = 122
      Height = 17
      Caption = #19978#27425#39044#35745#25209#38144#25240#25187
      Checked = True
      State = cbChecked
      TabOrder = 9
      OnClick = cblastyjpxClick
    end
    object cbadddot: TCheckBox
      Left = 417
      Top = 393
      Width = 82
      Height = 17
      Caption = #38468#21152#28857#35774#32622
      TabOrder = 10
      OnClick = cbadddotClick
    end
    object cbrkallsupplier: TCheckBox
      Left = 25
      Top = 290
      Width = 233
      Height = 17
      Caption = #20837#24211#26126#32454#26174#31034#25152#26377#20379#24212#21830#30340#21382#21490#35760#24405
      TabOrder = 11
    end
    object cbrkusefind: TCheckBox
      Left = 320
      Top = 197
      Width = 177
      Height = 17
      Caption = #21551#29992#20837#24211#26597#21333#23494#30721
      TabOrder = 12
    end
    object cbrkusedelete: TCheckBox
      Left = 25
      Top = 197
      Width = 209
      Height = 17
      Caption = #21551#29992#20837#24211#21024#21333#23494#30721
      TabOrder = 13
    end
    object cbrkusetuihuo: TCheckBox
      Left = 25
      Top = 222
      Width = 169
      Height = 17
      Caption = #21551#29992#20837#24211#36864#36135#23494#30721
      TabOrder = 14
    end
    object chmutisupplier: TCheckBox
      Left = 319
      Top = 38
      Width = 114
      Height = 17
      Caption = #21551#29992#22810#36135#28304
      TabOrder = 15
      Visible = False
    end
    object chdeletestack: TCheckBox
      Left = 24
      Top = 64
      Width = 169
      Height = 17
      Caption = #26377#24211#23384#24341#29992#21487#21024#38500#24211#20301
      TabOrder = 16
    end
    object edmonth: TEdit
      Left = 167
      Top = 88
      Width = 49
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 17
      Text = '3'
    end
    object GroupBox4: TGroupBox
      Left = 18
      Top = 182
      Width = 521
      Height = 5
      TabOrder = 18
    end
    object GroupBox5: TGroupBox
      Left = 18
      Top = 249
      Width = 521
      Height = 5
      TabOrder = 19
    end
    object cbrkusechange: TCheckBox
      Left = 320
      Top = 220
      Width = 169
      Height = 17
      Caption = #21551#29992#20837#24211#20462#25913#21333#22836#23494#30721
      TabOrder = 20
    end
    object GroupBox3: TGroupBox
      Left = 18
      Top = 320
      Width = 521
      Height = 5
      TabOrder = 21
    end
    object cblastyjlsdiscount: TCheckBox
      Left = 320
      Top = 364
      Width = 145
      Height = 17
      Caption = #36319#36394#19978#27425#39044#35745#38646#21806#25240#25187
      TabOrder = 22
    end
    object chstoragesametishi: TCheckBox
      Left = 184
      Top = 13
      Width = 113
      Height = 17
      Caption = #37325#22797#20837#24211#24405#20837#25552#37266
      TabOrder = 23
    end
    object chrktuihuoguanli: TCheckBox
      Left = 319
      Top = 64
      Width = 114
      Height = 17
      Caption = #21551#29992#36864#36135#30417#31649
      TabOrder = 24
    end
    object edtkmouth: TEdit
      Left = 183
      Top = 117
      Width = 18
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 25
      Text = '3'
      Visible = False
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 422
      Width = 521
      Height = 5
      TabOrder = 26
    end
    object rg: TRadioGroup
      Left = 151
      Top = 431
      Width = 386
      Height = 40
      Margins.Top = 1
      Columns = 3
      ItemIndex = 0
      Items.Strings = (
        #20808#36827#20808#20986
        #20302#25240#25187#20808#20986
        #25163#21160#36873#25321)
      TabOrder = 27
    end
    object chcrtuserbarcode: TCheckBox
      Left = 319
      Top = 121
      Width = 123
      Height = 17
      Caption = #33258#21160#20135#29983#38468#21152#26465#30721
      TabOrder = 28
    end
    object cbtuihuo: TComboBox
      Left = 24
      Top = 143
      Width = 113
      Height = 25
      ItemHeight = 17
      ItemIndex = 0
      TabOrder = 29
      Text = #20379#24212#21830
      Items.Strings = (
        #20379#24212#21830
        #31867#21035
        #32479#19968)
    end
    object cbyouxian: TComboBox
      Left = 143
      Top = 143
      Width = 73
      Height = 25
      ItemHeight = 17
      ItemIndex = 0
      TabOrder = 30
      Text = #19968#32423#20248#20808
      Items.Strings = (
        #19968#32423#20248#20808
        #20108#32423#20248#20808
        #19977#32423#20248#20808)
    end
    object cbcaigoucayi: TCheckBox
      Left = 184
      Top = 64
      Width = 113
      Height = 17
      Caption = #37319#36141#20837#24211#24046#24322#25552#37266
      TabOrder = 31
    end
    object cbsamerkyx: TCheckBox
      Left = 319
      Top = 13
      Width = 114
      Height = 17
      Caption = #20801#35768#20837#36864#37325#22797#24405#20837
      TabOrder = 32
    end
    object cbsamerkts: TCheckBox
      Left = 439
      Top = 13
      Width = 113
      Height = 17
      Caption = #20837#36864#37325#22797#24405#20837#25552#37266
      TabOrder = 33
    end
    object cbcaigoudiscount: TCheckBox
      Left = 168
      Top = 331
      Width = 129
      Height = 17
      Caption = #36319#36394#37319#36141#25240#25187'('#30465#20195')'
      TabOrder = 34
    end
    object cbrukufeishendaicaigou: TCheckBox
      Left = 167
      Top = 364
      Width = 147
      Height = 17
      Caption = #36319#36394#37319#36141#25240#25187'('#38750#30465#20195')'
      TabOrder = 35
    end
    object cbqfsupplier: TCheckBox
      Left = 354
      Top = 149
      Width = 97
      Height = 17
      Caption = #21306#20998#20379#24212#21830
      TabOrder = 36
    end
    object cbqfclient: TCheckBox
      Left = 448
      Top = 149
      Width = 97
      Height = 17
      Caption = #21306#20998#23458#25143
      TabOrder = 37
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 624
    Top = 296
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 512
    Top = 35
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 584
    Top = 368
  end
end
