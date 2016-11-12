object frmfddetail: Tfrmfddetail
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #36820#28857#26126#32454
  ClientHeight = 418
  ClientWidth = 791
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DBGridEh1: TDBGridEh
    Left = 8
    Top = 8
    Width = 769
    Height = 367
    DataSource = DataSource1
    Flat = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'Tahoma'
    FooterFont.Style = []
    FooterRowCount = 1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    SumList.Active = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        EditButtons = <>
        FieldName = 'retailntcode'
        Footer.Value = #21512#35745
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #38646#21806#21333#21495
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 110
      end
      item
        EditButtons = <>
        FieldName = 'hdtime'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #26085#26399
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 130
      end
      item
        EditButtons = <>
        FieldName = 'isbn'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = 'ISBN'
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 100
      end
      item
        EditButtons = <>
        FieldName = 'name'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 160
      end
      item
        EditButtons = <>
        FieldName = 'amount'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #25968#37327
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 40
      end
      item
        EditButtons = <>
        FieldName = 'price'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 40
      end
      item
        EditButtons = <>
        FieldName = 'abbreviatedname'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#31038
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 70
      end
      item
        EditButtons = <>
        FieldName = 'totalvalue'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24635#36820#28857
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 50
      end
      item
        EditButtons = <>
        FieldName = 'disvalue'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #21333#26412#36820#28857
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
      end>
  end
  object Button1: TButton
    Left = 584
    Top = 381
    Width = 81
    Height = 28
    Caption = #25171#21360
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 671
    Top = 381
    Width = 81
    Height = 28
    Caption = #39044#35272
    TabOrder = 2
    OnClick = Button2Click
  end
  object aq: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'exec TeacherFDSearchDetail 2,'#39'1998-01-01'#39','#39'2090-01-01'#39)
    Left = 288
    Top = 136
  end
  object DataSource1: TDataSource
    DataSet = aq
    Left = 272
    Top = 232
  end
  object frxfddetail: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41869.567155439800000000
    ReportOptions.LastChange = 42008.659190046300000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    OnGetValue = frxfddetailGetValue
    Left = 392
    Top = 200
  end
  object frxDBDataset1: TfrxDBDataset
    UserName = 'frxDBDataset1'
    CloseDataSource = False
    DataSet = aq
    Left = 376
    Top = 144
  end
end
