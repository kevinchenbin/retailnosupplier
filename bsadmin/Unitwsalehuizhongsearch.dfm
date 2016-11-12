object frmwsalehuizhong: Tfrmwsalehuizhong
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsSingle
  Caption = #25209#38144#27719#24635#26597#35810
  ClientHeight = 722
  ClientWidth = 1022
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object rztlbr1: TRzToolbar
    Left = 0
    Top = 0
    Width = 1022
    Height = 36
    AutoResize = False
    AutoStyle = False
    Margin = 1
    TopMargin = 4
    ButtonWidth = 60
    ShowButtonCaptions = True
    ShowDivider = False
    TextOptions = ttoSelectiveTextOnRight
    WrapControls = False
    BorderInner = fsFlatRounded
    BorderOuter = fsNone
    BorderSides = [sdTop, sdBottom]
    BorderWidth = 0
    Caption = #21024#38500
    Color = 16113353
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    GradientColorStyle = gcsMSOffice
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      tlbtn8
      BtnNew
      RzToolButton1
      RzToolButton2
      BtnAlignBottom
      tlbtn7
      toolshowmainmenu)
    object tlbtn8: TRzToolButton
      Tag = 1
      Left = 1
      Top = -2
      Width = 55
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#35810#13'[F1]'
      OnClick = tlbtn8Click
    end
    object tlbtn7: TRzToolButton
      Left = 281
      Top = -2
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = tlbtn7Click
    end
    object BtnNew: TRzToolButton
      Tag = 2
      Left = 56
      Top = -2
      Width = 55
      Height = 36
      Hint = 'New'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'[F2]'
      OnClick = BtnNewClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 221
      Top = -2
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 27
      GradientColorStyle = gcsSystem
      ImageIndex = 26
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26368#23567#21270#13'(N)'
      OnClick = BtnAlignBottomClick
    end
    object RzToolButton1: TRzToolButton
      Tag = 2
      Left = 111
      Top = -2
      Width = 55
      Height = 36
      Hint = 'New'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25171#21360#13'[F3]'
      OnClick = RzToolButton1Click
    end
    object RzToolButton2: TRzToolButton
      Tag = 2
      Left = 166
      Top = -2
      Width = 55
      Height = 36
      Hint = 'New'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #39044#35272#13'[F4]'
      OnClick = RzToolButton2Click
    end
    object toolshowmainmenu: TRzToolButton
      Left = 341
      Top = -2
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26174#31034#13#20027#33756#21333
      OnClick = toolshowmainmenuClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 36
    Width = 1022
    Height = 686
    Align = alClient
    BevelInner = bvLowered
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 1
    object Label1: TLabel
      Left = 104
      Top = 650
      Width = 24
      Height = 17
      Caption = #21512#35745
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 272
      Top = 650
      Width = 36
      Height = 17
      Caption = #24635#25968#37327
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 582
      Top = 650
      Width = 36
      Height = 17
      Caption = #24635#23454#27915
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 429
      Top = 650
      Width = 36
      Height = 17
      Caption = #24635#30721#27915
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object GroupBox1: TGroupBox
      Left = 11
      Top = 6
      Width = 990
      Height = 105
      Caption = #26597#35810#26465#20214
      TabOrder = 0
      object Label2: TLabel
        Left = 230
        Top = 25
        Width = 12
        Height = 17
        Caption = #21040
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object cbruku: TCheckBox
        Left = 22
        Top = 25
        Width = 73
        Height = 17
        Caption = #26085#26399
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object cbstag: TCheckBox
        Left = 623
        Top = 25
        Width = 42
        Height = 17
        Caption = #24215#21495
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
      object dtpend: TDateTimePicker
        Left = 247
        Top = 21
        Width = 121
        Height = 25
        Date = 40909.661257361110000000
        Time = 40909.661257361110000000
        Checked = False
        Color = clWhite
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        MinDate = 40909.000000000000000000
        ParentFont = False
        TabOrder = 2
        OnChange = dtpstartChange
      end
      object dtpstart: TDateTimePicker
        Left = 101
        Top = 21
        Width = 123
        Height = 25
        Date = 40909.661257361110000000
        Time = 40909.661257361110000000
        Color = clWhite
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        MinDate = 40909.000000000000000000
        ParentFont = False
        TabOrder = 3
        OnChange = dtpstartChange
      end
      object cbfahuofanshi: TCheckBox
        Left = 390
        Top = 25
        Width = 72
        Height = 17
        Caption = #21457#36135#26041#24335
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 4
      end
      object cbfahuo: TComboBox
        Left = 468
        Top = 21
        Width = 123
        Height = 25
        Style = csDropDownList
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ItemHeight = 17
        ItemIndex = 0
        ParentFont = False
        TabOrder = 5
        Text = #31038#30452#21457
        OnChange = cbfahuoChange
        Items.Strings = (
          #31038#30452#21457
          #28100#36716#21457)
      end
      object cbstgcheck: TComboBox
        Left = 671
        Top = 21
        Width = 123
        Height = 25
        Style = csDropDownList
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ItemHeight = 17
        ParentFont = False
        TabOrder = 6
        OnChange = cbstgcheckChange
      end
      object cbfahuocheck: TCheckBox
        Left = 22
        Top = 64
        Width = 73
        Height = 17
        Caption = #21457#36135
        Checked = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        State = cbChecked
        TabOrder = 7
      end
      object cbfahuotuihuo: TCheckBox
        Left = 101
        Top = 64
        Width = 73
        Height = 17
        Caption = #21457#36135#36864#36135
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 8
      end
    end
    object RzDBGrid1: TRzDBGrid
      Left = 740
      Top = 117
      Width = 273
      Height = 524
      DataSource = dshead
      DefaultDrawing = True
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'clientname'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = #24494#36719#38597#40657
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #23458#25143
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'WsaleNtCodeStr'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = #24494#36719#38597#40657
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Headamount'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = #24494#36719#38597#40657
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HeadFixed'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = #24494#36719#38597#40657
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HeadDis'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = #24494#36719#38597#40657
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = #24494#36719#38597#40657
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = #24494#36719#38597#40657
          Font.Style = []
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
          Visible = True
        end>
    end
    object dbgrid1: TRzDBGrid
      Left = 11
      Top = 117
      Width = 723
      Height = 524
      DataSource = ds
      DefaultDrawing = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnCellClick = dbgrid1CellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'xuhao'
          Title.Alignment = taCenter
          Title.Caption = #24207#21495
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 30
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Barcode'
          Title.Alignment = taCenter
          Title.Caption = #20070#21495
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'bookname'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UserDefCode'
          Title.Alignment = taCenter
          Title.Caption = #33258#32534#30721
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'avgdiscount'
          Title.Alignment = taCenter
          Title.Caption = #24179#22343#25240#25187'%'
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
          Visible = True
        end>
    end
    object RzNumericEdit1: TRzNumericEdit
      Left = 314
      Top = 647
      Width = 110
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 3
      DisplayFormat = '0;(0)'
    end
    object RzNumericEdit2: TRzNumericEdit
      Left = 466
      Top = 647
      Width = 110
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
      DisplayFormat = '####.#0;-####.#0'
    end
    object RzNumericEdit3: TRzNumericEdit
      Left = 624
      Top = 647
      Width = 110
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 5
      DisplayFormat = '####.#0;-####.#0'
    end
  end
  object aqdetail: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 216
    Top = 304
  end
  object ds: TDataSource
    DataSet = aqdetail
    Left = 296
    Top = 304
  end
  object aqhead: TADOQuery
    Parameters = <
      item
        Name = 'bn'
        DataType = ftString
        Size = 2000
        Value = Null
      end
      item
        Name = 'uc'
        DataType = ftString
        Size = 100
        Value = Null
      end
      item
        Name = 'pc'
        DataType = ftFloat
        Size = 100
        Value = Null
      end
      item
        Name = 'bcode'
        DataType = ftString
        Size = 20
        Value = Null
      end
      item
        Name = 'pcount'
        DataType = ftString
        Size = 200
        Value = Null
      end
      item
        Name = 'abb'
        DataType = ftString
        Size = 2000
        Value = Null
      end>
    SQL.Strings = (
      
        'select convert(nvarchar(10),hdtime,120) as hdtime,bkcatalogid,cl' +
        'ientname,headfixed,headdis,headamount,wsalentcodestr '
      'from Qry_WsaleHuiZhongQuery '
      
        'where bookname=:bn and userdefcode=:uc and price=:pc and barcode' +
        ' = :bcode and presscount=:pcount and abbreviatedname=:abb'
      
        'group by hdtime,bkcatalogid,clientname,headfixed,headdis,headamo' +
        'unt,wsalentcodestr')
    Left = 440
    Top = 344
  end
  object dshead: TDataSource
    DataSet = aqhead
    Left = 360
    Top = 368
  end
  object frxhuizhong: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = '\\WIN-66QK65T9K6A\Canon LBP2900'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40494.609668310200000000
    ReportOptions.LastChange = 41024.411124722200000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{                                              '
      '}')
    StoreInDFM = False
    OnGetValue = frxhuizhongGetValue
    Left = 536
    Top = 192
  end
  object frxDBDataset1: TfrxDBDataset
    UserName = 'frxDBDataset1'
    CloseDataSource = False
    DataSet = aqdetail
    Left = 504
    Top = 248
  end
  object savedlg: TSaveDialog
    Left = 400
    Top = 80
  end
end
