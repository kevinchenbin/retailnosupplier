inherited frmRetailNote: TfrmRetailNote
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #38646#21806#25171#21360
  ClientHeight = 359
  ClientWidth = 886
  Font.Charset = ANSI_CHARSET
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Position = poMainFormCenter
  ExplicitWidth = 892
  ExplicitHeight = 387
  PixelsPerInch = 96
  TextHeight = 17
  object Label3: TLabel [0]
    Left = 100
    Top = 590
    Width = 4
    Height = 20
    Font.Charset = ANSI_CHARSET
    Font.Color = clRed
    Font.Height = -14
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object labstorage: TLabel [1]
    Left = 9
    Top = 11
    Width = 56
    Height = 19
    Caption = #24403#21069#24215#65306
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -14
    Font.Name = #24494#36719#38597#40657
    Font.Style = [fsBold]
    ParentFont = False
  end
  object RzGroupBox4: TRzGroupBox [2]
    Left = 0
    Top = 0
    Width = 886
    Height = 359
    Align = alClient
    BorderColor = clInactiveCaptionText
    BorderSides = [sdLeft, sdTop, sdRight]
    Caption = #25171#21360#35774#32622
    Ctl3D = False
    ParentColor = True
    ParentCtl3D = False
    TabOrder = 0
    VisualStyle = vsClassic
    object RzLabel1: TRzLabel
      Left = 11
      Top = 29
      Width = 36
      Height = 17
      Caption = #27426#36814#35789
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel3: TRzLabel
      Left = 11
      Top = 67
      Width = 24
      Height = 17
      Caption = #22320#22336
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel4: TRzLabel
      Left = 11
      Top = 106
      Width = 48
      Height = 17
      Caption = #32852#31995#30005#35805
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel5: TRzLabel
      Left = 11
      Top = 146
      Width = 24
      Height = 17
      Caption = #22791#27880
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLine1: TRzLine
      Left = -2
      Top = 177
      Width = 444
      Height = 20
    end
    object RzLabel6: TRzLabel
      Left = 448
      Top = 29
      Width = 96
      Height = 17
      Caption = 'POS'#25171#21360#36830#25509#31471#21475
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel7: TRzLabel
      Left = 448
      Top = 67
      Width = 60
      Height = 17
      Caption = #21333#25454#21015#35774#32622
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl1: TRzLabel
      Left = 448
      Top = 97
      Width = 343
      Height = 17
      Caption = #28201#39336#25552#31034#65306#25152#36873#39033#30446#35831#19981#35201#36229#36807'4'#20010#65292#21542#21017#23558#20250#24433#21709#23567#31080#25171#21360#32654#35266
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object dbedtWelcomeMessage: TRzDBEdit
      Left = 65
      Top = 27
      Width = 353
      Height = 23
      DataSource = dsNotePrint
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
    end
    object dbedtAddress: TRzDBEdit
      Left = 65
      Top = 65
      Width = 353
      Height = 23
      DataSource = dsNotePrint
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
    end
    object dbedtTel: TRzDBEdit
      Left = 65
      Top = 104
      Width = 353
      Height = 23
      DataSource = dsNotePrint
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
    end
    object dbedtRemarks: TRzDBEdit
      Left = 65
      Top = 144
      Width = 353
      Height = 23
      DataSource = dsNotePrint
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
    end
    object CHKPrice: TRzDBCheckBox
      Left = 616
      Top = 67
      Width = 43
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #23450#20215
      TabOrder = 4
    end
    object CHKBookName: TRzDBCheckBox
      Left = 553
      Top = 67
      Width = 43
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #20070#21517
      TabOrder = 5
    end
    object CHKDiscount: TRzDBCheckBox
      Left = 752
      Top = 66
      Width = 43
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25240#25187
      TabOrder = 6
    end
    object btn1: TButton
      Left = 738
      Top = 317
      Width = 62
      Height = 24
      Caption = #20445#23384'[S]'
      TabOrder = 7
      OnClick = btn1Click
    end
    object btn2: TButton
      Left = 661
      Top = 317
      Width = 62
      Height = 24
      Caption = #25171#21360#27979#35797
      TabOrder = 8
      OnClick = btn2Cick
    end
    object CHKtotalamount: TRzDBCheckBox
      Left = 680
      Top = 66
      Width = 43
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25968#37327
      TabOrder = 9
    end
    object CHKjine: TRzDBCheckBox
      Left = 824
      Top = 66
      Width = 43
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #37329#39069
      TabOrder = 10
    end
    object CHKCardrec: TRzDBCheckBox
      Left = 11
      Top = 203
      Width = 127
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#20648#20540#21345#28040#36153#37329#39069
      TabOrder = 11
    end
    object CHKtotalhang: TRzDBCheckBox
      Left = 180
      Top = 206
      Width = 79
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#27719#24635#34892
      TabOrder = 12
    end
    object Button2: TButton
      Left = 484
      Top = 319
      Width = 93
      Height = 24
      Caption = #38065#31665#24182#21475'2'#27979#35797
      TabOrder = 13
      Visible = False
      OnClick = Button2Click
    end
    object dbcbbPort: TComboBox
      Left = 553
      Top = 26
      Width = 96
      Height = 25
      BevelKind = bkFlat
      Ctl3D = True
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 14
      Text = 'LPT1'
      Items.Strings = (
        'LPT1'
        'LPT2'
        'LPT3'
        'USB'
        'COM1'
        'COM2')
    end
    object chprintmayang: TRzDBCheckBox
      Left = 11
      Top = 279
      Width = 91
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#21407#20215#21512#35745
      TabOrder = 15
    end
    object chprintdiscount: TRzDBCheckBox
      Left = 327
      Top = 206
      Width = 91
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#25240#25187#37329#39069
      TabOrder = 16
    end
    object chkpostcard: TRzDBCheckBox
      Left = 11
      Top = 241
      Width = 127
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#38134#34892#21345#28040#36153#37329#39069
      TabOrder = 17
    end
    object chkyouhuiquan: TRzDBCheckBox
      Left = 180
      Top = 241
      Width = 127
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#20248#24800#21048#28040#36153#37329#39069
      TabOrder = 18
    end
    object rgtype: TRadioGroup
      Left = 688
      Top = 16
      Width = 175
      Height = 36
      Columns = 2
      Ctl3D = True
      ItemIndex = 0
      Items.Strings = (
        #23567#31080
        #26222#36890#31080#25454)
      ParentCtl3D = False
      TabOrder = 19
    end
    object chprintjifen: TRzDBCheckBox
      Left = 327
      Top = 279
      Width = 67
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#31215#20998
      TabOrder = 20
    end
    object chprintcard: TRzDBCheckBox
      Left = 11
      Top = 318
      Width = 103
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#20250#21592#21345#20313#39069
      TabOrder = 21
    end
    object chprintname: TRzDBCheckBox
      Left = 180
      Top = 318
      Width = 91
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25171#21360#20250#21592#22995#21517
      TabOrder = 22
    end
    object chjiaojieprint: TRzDBCheckBox
      Left = 327
      Top = 241
      Width = 103
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #20132#25509#29677#25171#21360#23567#31080
      TabOrder = 23
    end
    object chprint: TRzDBCheckBox
      Left = 180
      Top = 279
      Width = 115
      Height = 19
      DataSource = dsNotePrint
      ValueChecked = 'True'
      ValueUnchecked = 'False'
      Caption = #25910#27454#30452#25509#25171#21360#23567#31080
      TabOrder = 24
    end
    object btn3: TButton
      Left = 811
      Top = 316
      Width = 62
      Height = 25
      Caption = #36864#20986'[ESC]'
      TabOrder = 25
      OnClick = btn3Click
    end
    object GroupBox1: TGroupBox
      Left = 448
      Top = 123
      Width = 425
      Height = 121
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 26
      object Label1: TLabel
        Left = 14
        Top = 18
        Width = 60
        Height = 17
        Caption = #35831#36873#25321#31471#21475
      end
      object Label2: TLabel
        Left = 205
        Top = 18
        Width = 84
        Height = 17
        Caption = #35831#36755#20837#27979#35797#23383#31526
      end
      object rg1: TRadioGroup
        Left = 14
        Top = 42
        Width = 385
        Height = 38
        Caption = #29366#24577#28783
        Columns = 5
        ItemIndex = 0
        Items.Strings = (
          '(1)'#20840#26263
          '(2)'#21333#20215
          '(3)'#24635#35745
          '(4)'#25910#27454
          '(5)'#25214#38646)
        TabOrder = 0
      end
      object Button3: TButton
        Left = 339
        Top = 86
        Width = 60
        Height = 24
        Caption = #39038#26174#27979#35797
        TabOrder = 1
        OnClick = Button3Click
      end
      object cbcomnum: TComboBox
        Left = 80
        Top = 14
        Width = 89
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 2
        OnChange = cbcomnumChange
      end
      object ch1: TCheckBox
        Left = 220
        Top = 89
        Width = 113
        Height = 17
        Caption = #21551#29992#39038#23458#26174#31034#23631
        TabOrder = 3
      end
      object edtest: TEdit
        Left = 295
        Top = 14
        Width = 104
        Height = 25
        AutoSize = False
        MaxLength = 15
        TabOrder = 4
        Text = '8.8.8.8.8.8.8.8'
      end
    end
    object chyuying: TCheckBox
      Left = 327
      Top = 319
      Width = 113
      Height = 17
      Caption = #25910#27454#35821#38899#25552#31034
      TabOrder = 27
    end
    object GroupBox2: TGroupBox
      Left = 448
      Top = 250
      Width = 425
      Height = 57
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 28
      object Label4: TLabel
        Left = 16
        Top = 20
        Width = 51
        Height = 17
        Caption = #38065#31665#25509#21475':'
      end
      object Label5: TLabel
        Left = 151
        Top = 20
        Width = 27
        Height = 17
        Caption = #25509#21475':'
      end
      object cbmoneybox: TComboBox
        Left = 73
        Top = 18
        Width = 64
        Height = 25
        ItemHeight = 17
        ItemIndex = 0
        TabOrder = 0
        Text = 'LPT'
        OnChange = cbmoneyboxChange
        Items.Strings = (
          'LPT'
          'USB')
      end
      object Button1: TButton
        Left = 264
        Top = 12
        Width = 58
        Height = 36
        Caption = #38065#31665#27979#35797
        TabOrder = 1
        OnClick = Button1Click
      end
      object cbinterfacetype: TComboBox
        Left = 181
        Top = 18
        Width = 68
        Height = 25
        ItemHeight = 17
        ItemIndex = 0
        TabOrder = 2
        Text = 'LPT1'
        Items.Strings = (
          'LPT1'
          'LPT2')
      end
      object cbopenmoneybox: TCheckBox
        Left = 339
        Top = 24
        Width = 68
        Height = 17
        Caption = #25910#27454#24320#21551
        TabOrder = 3
      end
    end
  end
  inherited qryUserAuthority: TADOQuery
    Left = 256
    Top = 136
  end
  inherited aquerybs: TADOQuery
    Left = 320
    Top = 144
  end
  object qryRetailNoteName: TADOQuery
    Parameters = <>
    Left = 169
    Top = 112
  end
  object Ds1: TDataSource
    Left = 361
    Top = 65528
  end
  object dsNotePrint: TDataSource
    DataSet = dsetRetailNote
    Left = 304
    Top = 24
  end
  object dsetRetailNote: TADODataSet
    Parameters = <>
    Left = 256
    Top = 72
  end
  object ds2: TDataSource
    DataSet = dsPrint
    Left = 304
    Top = 144
  end
  object dsPrint: TADODataSet
    Parameters = <>
    Left = 344
    Top = 64
  end
  object dsretail: TADODataSet
    Parameters = <>
    Left = 352
    Top = 136
  end
  object ds4: TDataSource
    DataSet = dsretail
    Left = 408
    Top = 136
  end
  object con: TADOConnection
    Left = 256
  end
  object frxretail: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.AllowEdit = False
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    PrintOptions.ShowDialog = False
    ReportOptions.Compressed = True
    ReportOptions.CreateDate = 41050.432745416700000000
    ReportOptions.LastChange = 41050.603247962960000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    ShowProgress = False
    StoreInDFM = False
    Left = 112
    Top = 120
  end
end
