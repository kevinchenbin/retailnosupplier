object frmprintbarcode: Tfrmprintbarcode
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #38468#21152#26465#30721#25171#21360
  ClientHeight = 409
  ClientWidth = 423
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 423
    Height = 409
    Align = alClient
    BevelInner = bvLowered
    ParentBackground = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 2
      Top = 2
      Width = 419
      Height = 334
      Align = alTop
      Ctl3D = False
      DataSource = ds
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'name'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UserBarcode'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #26465#30721'('#38468#21152')'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 35
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'catalogid'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'Id'
          Visible = False
        end>
    end
    object RzButton1: TRzButton
      Left = 310
      Top = 342
      Caption = #30830#23450
      TabOrder = 1
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 310
      Top = 373
      Caption = #21462#28040
      TabOrder = 2
      OnClick = RzButton2Click
    end
    object RzButton3: TRzButton
      Tag = 1
      Left = 5
      Top = 342
      Caption = #39044#35272
      TabOrder = 3
      OnClick = RzButton3Click
    end
    object RzButton4: TRzButton
      Tag = 2
      Left = 5
      Top = 373
      Caption = #25171#21360
      TabOrder = 4
      OnClick = RzButton3Click
    end
    object RzButton5: TRzButton
      Tag = 1
      Left = 101
      Top = 342
      Width = 84
      Height = 56
      Caption = #33258#21160#29983#25104#26465#30721
      TabOrder = 5
      OnClick = RzButton5Click
    end
  end
  object fcon: TADOConnection
    Left = 264
    Top = 64
  end
  object query: TADOQuery
    Parameters = <>
    Left = 184
    Top = 80
  end
  object ds: TDataSource
    DataSet = query
    Left = 120
    Top = 152
  end
  object spdabao: TADOStoredProc
    ProcedureName = 'UserBarcode'
    Parameters = <
      item
        Name = '@userid'
        DataType = ftInteger
        Size = 10
        Value = Null
      end>
    Left = 56
    Top = 240
  end
  object querydabao: TADOQuery
    AutoCalcFields = False
    CursorType = ctStatic
    Parameters = <>
    Left = 272
    Top = 144
  end
  object frxdbpbag: TfrxDBDataset
    UserName = 'frxdbpbag'
    CloseDataSource = False
    Left = 288
    Top = 216
  end
  object frxpbag: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40612.668684201400000000
    ReportOptions.LastChange = 41763.638464710650000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    Left = 240
    Top = 272
  end
  object frxBarCodeObject1: TfrxBarCodeObject
    Left = 208
    Top = 216
  end
  object createbarcode: TADOQuery
    Parameters = <>
    Left = 48
    Top = 160
  end
end
