object frmPrint: TfrmPrint
  Left = 0
  Top = 0
  Caption = 'frmPrint'
  ClientHeight = 182
  ClientWidth = 320
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RvSystem1: TRvSystem
    TitleSetup = 'Output Options'
    TitleStatus = 'Report Status'
    TitlePreview = 'Report Preview'
    SystemOptions = [soAllowPrintFromPreview, soAllowSaveFromPreview, soPreviewModal]
    SystemFiler.StatusFormat = 'Generating page %p'
    SystemPreview.ZoomFactor = 100.000000000000000000
    SystemPrinter.ScaleX = 100.000000000000000000
    SystemPrinter.ScaleY = 100.000000000000000000
    SystemPrinter.StatusFormat = 'Printing page %p'
    SystemPrinter.Title = 'Rave Report'
    SystemPrinter.UnitsFactor = 1.000000000000000000
    Left = 216
    Top = 112
  end
  object prjretail: TRvProject
    Engine = RvSystem1
    Left = 40
    Top = 16
  end
  object conRVretail: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aquerybs
    Left = 112
    Top = 72
  end
  object aquerybs: TADOQuery
    Parameters = <>
    Left = 168
    Top = 24
  end
  object frxre: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    PrintOptions.ShowDialog = False
    ReportOptions.CreateDate = 41050.432745416700000000
    ReportOptions.LastChange = 41389.638358078700000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    ShowProgress = False
    StoreInDFM = False
    Left = 32
    Top = 64
  end
end
