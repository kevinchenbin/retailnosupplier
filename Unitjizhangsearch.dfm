object frmsearch: Tfrmsearch
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #38750#33829#21033#24615#25910#20837#26597#35810
  ClientHeight = 468
  ClientWidth = 564
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 17
  object GroupBox1: TGroupBox
    Left = 8
    Top = 42
    Width = 534
    Height = 105
    Caption = #26597#35810#26465#20214
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 457
      Top = 25
      Width = 65
      Height = 26
      Caption = #26597#35810
      OnClick = SpeedButton1Click
    end
    object Label2: TLabel
      Left = 255
      Top = 31
      Width = 12
      Height = 17
      Caption = #21040
    end
    object Label3: TLabel
      Left = 14
      Top = 31
      Width = 48
      Height = 17
      Caption = #26085#26399#36873#25321
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object dtpend: TRzDateTimePicker
      Left = 289
      Top = 27
      Width = 162
      Height = 25
      Date = 41065.467781886570000000
      Time = 41065.467781886570000000
      TabOrder = 0
    end
    object dtpbegin: TRzDateTimePicker
      Left = 68
      Top = 26
      Width = 162
      Height = 25
      Date = 41065.467864039350000000
      Time = 41065.467864039350000000
      TabOrder = 1
    end
    object cbbumen: TCheckBox
      Left = 24
      Top = 64
      Width = 49
      Height = 17
      Caption = #37096#38376
      TabOrder = 2
    end
    object cbkemu: TCheckBox
      Left = 241
      Top = 64
      Width = 45
      Height = 17
      Caption = #31185#30446
      TabOrder = 3
    end
    object cbstg: TComboBox
      Left = 68
      Top = 60
      Width = 162
      Height = 25
      BevelInner = bvNone
      BevelOuter = bvNone
      Style = csDropDownList
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 4
    end
    object cbkemus: TComboBox
      Left = 289
      Top = 59
      Width = 162
      Height = 25
      Style = csDropDownList
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 5
    end
  end
  object dg: TDBGridEh
    Left = 11
    Top = 153
    Width = 545
    Height = 305
    DataSource = ds
    Flat = True
    FooterColor = clWindow
    FooterFont.Charset = ANSI_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -12
    FooterFont.Name = #24494#36719#38597#40657
    FooterFont.Style = []
    FooterRowCount = 1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    SumList.Active = True
    TabOrder = 1
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Columns = <
      item
        EditButtons = <>
        FieldName = 'jizhangdate'
        Footer.Value = #21512#35745
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #26085#26399
        Width = 70
      end
      item
        EditButtons = <>
        FieldName = 'kemu'
        Footers = <>
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #31185#30446
        Width = 90
      end
      item
        EditButtons = <>
        FieldName = 'jimoney'
        Footer.FieldName = 'jimoney'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #25910#25903
        Width = 80
      end
      item
        AlwaysShowEditButton = True
        AutoDropDown = True
        AutoFitColWidth = False
        ButtonStyle = cbsNone
        DropDownShowTitles = True
        DropDownSizing = True
        EditButtons = <>
        FieldName = 'department'
        Footers = <>
        NotInKeyListIndex = 0
        Title.Alignment = taCenter
        Title.Caption = #37096#38376
        Width = 90
      end
      item
        EditButtons = <>
        FieldName = 'bk'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Width = 160
      end
      item
        EditButtons = <>
        FieldName = 'ID'
        Footers = <>
        Visible = False
      end>
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 564
    Height = 36
    AutoResize = False
    AutoStyle = False
    TopMargin = 6
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsFlatRounded
    BorderOuter = fsNone
    BorderSides = [sdTop, sdBottom]
    BorderWidth = 0
    Color = 16113353
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    GradientColorStyle = gcsMSOffice
    ParentFont = False
    TabOrder = 2
    VisualStyle = vsClassic
    ToolbarControls = (
      RzToolButton1
      RzToolButton2
      BtnExit)
    object BtnExit: TRzToolButton
      Left = 124
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
    object RzToolButton1: TRzToolButton
      Left = 4
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25171#21360#13'(&P)'
      OnClick = RzToolButton1Click
    end
    object RzToolButton2: TRzToolButton
      Left = 64
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #39044#35272#13'(&Y)'
      OnClick = RzToolButton2Click
    end
  end
  object con: TADOConnection
    Left = 464
    Top = 240
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 416
    Top = 320
  end
  object ds: TDataSource
    DataSet = aq
    Left = 296
    Top = 264
  end
  object frxjizhang: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41067.418635057900000000
    ReportOptions.LastChange = 41339.655188877300000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    OnGetValue = frxjizhangGetValue
    Left = 400
    Top = 240
  end
  object frxdb: TfrxDBDataset
    UserName = 'frxdb'
    CloseDataSource = False
    DataSet = aq
    Left = 344
    Top = 248
  end
end
