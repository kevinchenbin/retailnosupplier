object frmwsaleprinta: Tfrmwsaleprinta
  Left = 0
  Top = 0
  Caption = 'frmwsaleprinta'
  ClientHeight = 433
  ClientWidth = 920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object wholesale: TRvProject
    Engine = RvSystem1
    Left = 152
    Top = 288
  end
  object aqHeader: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select A.Remarks,D.printtitle as printName,A.WsaleNtCodeStr,F.Ad' +
        'dress,F.Contact,D.tel,A.WsaleNtCode,F.Name,F.telephone,A.hdtime ' +
        ',A.hdtime  as maketime ,A.fixedprice,A.discountedprice,'
      
        'A.totalamount,A.addcosts,C.name as maker,A.Checked,A.Nochecked  ' +
        'from BS_WsaleNoteHeader A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.vendorid = F.ID'
      'where A.ID =:ID'
      ''
      ''
      '')
    Left = 40
    Top = 280
  end
  object RvDataSetConnection1: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqHeader
    Left = 112
    Top = 208
  end
  object aqdetail: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 32
    Top = 224
  end
  object RvDataSetConnection2: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqdetail
    Left = 232
    Top = 96
  end
  object aqtotalnum: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'headID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      'select count(*) as num from BS_WsaleNote'
      'where wsalentheaderid=:headID')
    Left = 216
    Top = 232
  end
  object RvDataSetConnection3: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqtotalnum
    Left = 352
    Top = 96
  end
  object RvSystem1: TRvSystem
    TitleSetup = 'Output Options'
    TitleStatus = 'Report Status'
    TitlePreview = 'Report Preview'
    SystemFiler.StatusFormat = 'Generating page %p'
    SystemPreview.ZoomFactor = 100.000000000000000000
    SystemPrinter.ScaleX = 100.000000000000000000
    SystemPrinter.ScaleY = 100.000000000000000000
    SystemPrinter.StatusFormat = 'Printing page %p'
    SystemPrinter.Title = 'Rave Report'
    SystemPrinter.UnitsFactor = 1.000000000000000000
    Left = 104
    Top = 272
  end
  object rvstorage1: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqhead
    Left = 264
    Top = 160
  end
  object rvstorage2: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqrvstoragedetail
    Left = 168
    Top = 168
  end
  object aqrvstoragedetail: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select RANK() OVER(order by A.ID asc) as xuhao,rtrim(C.ISBN) as ' +
        'ISBN,rtrim(C.Name) as Name,rtrim(C.PressCount) as PressCount,rtr' +
        'im(C.UserDefCode) as UserDefCode,rtrim(E.abbreviatedname) as abb' +
        'reviatedname ,rtrim(C.author) as author ,rtrim(C.price) as price' +
        ',A.amount,A.discount,A.fixedprice,discountedprice '
      'from BS_StorageNote A'
      'left join STK_BookInfo B on A.bkinfoid = B.ID'
      'left join BS_BookCatalog C on B.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      'where stgNtHeaderid =:ID'
      'order by A.id asc')
    Left = 184
    Top = 24
  end
  object aqhead: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select A.remarks,D.Address,F.Contact,D.tel,A.Stgntcode,A.stgntco' +
        'destr,F.Name,F.address as saddress,F.telephone,A.hdtime,A.totalf' +
        'ixedprice,A.totaldiscountedprice,'
      
        'A.totalamount,A.stgntcodestr,A.addcosts,C.name as op  from BS_St' +
        'orageNoteHeader A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.supplierid = F.ID'
      'where A.ID = :ID')
    Left = 72
    Top = 112
  end
  object aqorderhead: TADOQuery
    CursorType = ctStatic
    EnableBCD = False
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftString
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      
        'select D.printtitle as Name,D.Address,D.Contact,D.tel,A.OrderNtC' +
        'ode,A.orderStr,A.remarks,F.Name as clientname,F.contact as conta' +
        'ctor,F.telephone,convert(varchar(20),A.hdtime,23) as hdtime,conv' +
        'ert(varchar(20),A.hdtime,23) as maketime ,A.fixedprice,A.discoun' +
        'tedprice,'
      
        'A.totalamount,A.addcosts,C.name as maker ,F.address as clientadd' +
        ' from bs_ordernoteheader A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.vendorid = F.ID'
      'where A.ID =:ID')
    Left = 392
    Top = 24
  end
  object aqorderdetail: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftString
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      
        'select RANK() OVER(order by A.ID asc) as xuhao,rtrim(C.ISBN) as ' +
        'ISBN,rtrim(C.Name) as Name,rtrim(C.UserDefCode) as UserDefCode,r' +
        'trim(C.PressCount) as PressCount,rtrim(E.abbreviatedname) as abb' +
        'reviatedname,rtrim(C.author) as author,rtrim(C.price) as price,'
      'A.amount,A.discount,A.fixedprice,discountedprice'
      ' from bs_ordernote A'
      'left join BS_BookCatalog C on A.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      'where A.OrderNtHeaderID=:ID and A.state = 0'
      'order by A.id asc')
    Left = 464
    Top = 8
  end
  object rvorderdetail: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqorderdetail
    Left = 472
    Top = 112
  end
  object rvorderhead: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqorderhead
    Left = 576
    Top = 112
  end
  object aqProcureHeader: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        DataType = ftString
        Size = 10
        Value = Null
      end>
    SQL.Strings = (
      
        'select D.Address,F.Contact,D.tel,A.ProcureNtCode,A.procurestr,A.' +
        'remarks,F.Name,F.telephone,convert(varchar(20),A.hdtime,23) as h' +
        'dtime,convert(varchar(20),A.hdtime,23) as maketime ,A.fixedprice' +
        ',A.discountedprice,A.inorder,'
      
        'A.totalamount,A.addcosts,C.name as maker ,F.address as clientadd' +
        ',F.Fax,C.tel as usertel from BS_ProcureNoteHeader A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.supplierid = F.ID'
      'where A.ID =:ID')
    Left = 448
    Top = 168
  end
  object aqProcureDetail: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        DataType = ftString
        Size = 10
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select RANK() OVER(order by A.ID asc) as xuhao,C.ISBN,C.Name,C.P' +
        'ressCount,C.UserDefCode,E.abbreviatedname,rtrim(C.author) as aut' +
        'hor,C.price,'
      
        'A.amount,A.discount,A.fixedprice,discountedprice,rtrim(A.clientn' +
        'ame) as clientname,rtrim(A.ordercode) as ordercode'
      ' from bs_procurenote A'
      'left join BS_BookCatalog C on A.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      'where A.ProcureNtHeaderID=:ID'
      'order by A.ID asc')
    Left = 552
    Top = 184
  end
  object rvProcureDetail: TRvDataSetConnection
    RuntimeVisibility = rtEndUser
    DisableDataSource = False
    RestoreDataSet = False
    DataSet = aqProcureDetail
    Left = 456
    Top = 240
  end
  object rvProcureHead: TRvDataSetConnection
    RuntimeVisibility = rtEndUser
    DisableDataSource = False
    RestoreDataSet = False
    DataSet = aqProcureHeader
    Left = 544
    Top = 240
  end
  object rvstoragechashu: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqstoragechashu
    Left = 248
    Top = 48
  end
  object aqstoragechashu: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        DataType = ftInteger
        Value = Null
      end>
    SQL.Strings = (
      
        'select RANK() OVER(order by A.ID asc) as xuhao,C.ISBN,C.Name,E.a' +
        'bbreviatedname,C.author,C.UserDefCode,C.PressCount,C.price,F.har' +
        'mnum, F.damagenum,(F.harmnum + F.damagenum) as amount,A.discount' +
        ',(F.harmnum + F.damagenum)*C.price as fixedprice,(F.harmnum + F.' +
        'damagenum)*C.price*A.discount/100 as discountedprice '
      'from BS_StorageNote A'
      'left join STK_BookInfo B on A.bkinfoid = B.ID'
      'left join BS_BookCatalog C on B.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      
        'left join BS_StorageNote_attachment F on A.id = F.BS_StorageNote' +
        'ID'
      
        'where A.stgNtHeaderid = :ID and (F.harmnum > 0 or F.damagenum > ' +
        '0)'
      'order by A.ID asc')
    Left = 304
  end
  object fcon: TADOConnection
    Left = 344
    Top = 208
  end
  object frxdbprohead: TfrxDBDataset
    UserName = 'frxdbprohead'
    CloseDataSource = False
    DataSet = aqProcureHeader
    Left = 368
    Top = 256
  end
  object frxdbprodetail: TfrxDBDataset
    UserName = 'frxdbprodetail'
    CloseDataSource = False
    DataSet = aqProcureDetail
    Left = 320
    Top = 320
  end
  object frxDBwsalehead: TfrxDBDataset
    UserName = 'frxDBwsalehead'
    CloseDataSource = False
    DataSet = aqHeader
    Left = 264
    Top = 216
  end
  object frxCrossObject1: TfrxCrossObject
    Left = 328
    Top = 376
  end
  object frxRichObject1: TfrxRichObject
    Left = 392
    Top = 216
  end
  object frxOrder: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40497.719494537000000000
    ReportOptions.LastChange = 41023.747566550920000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    OnGetValue = frxOrderGetValue
    Left = 304
    Top = 224
  end
  object frxDBorddetail: TfrxDBDataset
    UserName = 'frxDBorddetail'
    CloseDataSource = False
    DataSet = aqorderdetail
    Left = 520
    Top = 64
  end
  object frxDBordhead: TfrxDBDataset
    UserName = 'frxDBordhead'
    CloseDataSource = False
    DataSet = aqorderhead
    Left = 592
    Top = 48
  end
  object frxstorage: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40497.719494537000000000
    ReportOptions.LastChange = 41334.689687789350000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    OnBeforePrint = frxstorageBeforePrint
    OnGetValue = frxstorageGetValue
    Left = 32
    Top = 8
  end
  object frxDBstohead: TfrxDBDataset
    UserName = 'frxDBstohead'
    CloseDataSource = False
    DataSet = aqhead
    Left = 32
    Top = 64
  end
  object frxDBstodetail: TfrxDBDataset
    UserName = 'frxDBstodetail'
    CloseDataSource = False
    DataSet = aqrvstoragedetail
    Left = 104
    Top = 56
  end
  object frxWsaleA4: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 38006.786384259300000000
    ReportOptions.LastChange = 41406.702844155090000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      
        'void Cross1OnCalcWidth(int ColumnIndex, variant ColumnValues, fl' +
        'oat &Width)'
      '{'
      '    if (VarToStr(ColumnValues[0]) == "'#20869#37096#35782#21035#30721'")     '
      '       {'
      '               Width = <"incode"> ;  '
      '       }           '
      '       if (VarToStr(ColumnValues[0]) == "'#20070#21495'")   '
      '       {'
      '               Width = <"ISBN"> ;  '
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#20070#21517'")'
      '       {'
      '               Width = <"CatalogName">;'
      '       }  '
      '       if (VarToStr(ColumnValues[0]) == "'#23450#20215'")   '
      '       {'
      '               Width = <"Price">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#20316#32773'")   '
      '       {'
      '               Width = <"Author">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#20986#29256#31038'")'
      '       {  '
      '               Width = <"AbbreviatedName">;  '
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#20986#29256#26085#26399'")   '
      '       {'
      '               Width = <"Pressdate">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#29256#27425'")   '
      '       {'
      '               Width = <"PressCount">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#23383#25968'")'
      '       {  '
      '               Width = <"BookWords">;'
      '       }                            '
      '       if (VarToStr(ColumnValues[0]) =="'#25968#37327'")'
      '       {  '
      '               Width = <"Amount">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) =="'#25240#25187'")'
      '       {  '
      '               Width = <"Discount">;'
      '       }'
      ''
      '       if (VarToStr(ColumnValues[0]) =="'#30721#27915'")'
      '       {  '
      '               Width = <"FixedPrice">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#23454#27915'")'
      '       {  '
      '               Width = <"DiscountedPrice">;'
      '       }'
      '    '
      '       if (VarToStr(ColumnValues[0]) =="'#33719#22870#24773#20917'")'
      '       {  '
      '               Width = <"huojiangstate">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#26657#21306'")   '
      '       {'
      '               Width = <"xiaoqu">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#23398#38498'")   '
      '       {'
      '               Width = <"xueyuan">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#35838#31243#21517#31216'")'
      '       {  '
      '               Width = <"course">;'
      '       }    '
      '}'
      ''
      '{}    ')
    StoreInDFM = False
    Left = 192
    Top = 384
  end
  object frxProcure: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40494.609668310200000000
    ReportOptions.LastChange = 41024.411124722200000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{                                              '
      '}')
    StoreInDFM = False
    OnGetValue = frxProcureGetValue
    Left = 256
    Top = 320
  end
  object frxWsale: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41406.006934976900000000
    ReportOptions.LastChange = 41406.013694884260000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      ''
      'begin'
      ''
      'end.')
    StoreInDFM = False
    OnBeforePrint = frxWsale2BeforePrint
    OnGetValue = frxWsale2GetValue
    Left = 208
    Top = 280
  end
  object frxWsalemuilprint: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41257.682618506900000000
    ReportOptions.LastChange = 41434.610031435190000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{'
      ''
      '}')
    StoreInDFM = False
    OnGetValue = frxWsalemuilprintGetValue
    Left = 576
    Top = 264
  end
  object frxmutildetail: TfrxDBDataset
    UserName = 'frxmutildetail'
    CloseDataSource = False
    DataSet = aqmuildetail
    Left = 520
    Top = 336
  end
  object aqmuilprinthead: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'id'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      
        'select  a.id,a.totalamount,a.addcosts,a.fixedprice,a.remarks,a.d' +
        'iscountedprice,a.wsalentcodestr as wsalentcode,convert(varchar(1' +
        '0),a.hdtime,120) as hdtime,c.name as clientname,u.name as opname'
      ' from dbo.BS_WsaleNoteHeader a left join dbo.CUST_CustomerInfo c'
      'on a.vendorid = c.id left join sys_user u'
      'on a.operatorid = u.id'
      'where a.id=:id')
    Left = 552
    Top = 384
  end
  object dsmuilprint: TDataSource
    DataSet = aqmuilprinthead
    Left = 384
    Top = 312
  end
  object aqmuildetail: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 448
    Top = 384
  end
  object frxdbwsalemuilprint: TfrxDBDataset
    UserName = 'frxdbwsalemuilprint'
    CloseDataSource = False
    DataSet = aqmuilprinthead
    Left = 440
    Top = 328
  end
  object frxsehngdaicaigou: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41257.682618506900000000
    ReportOptions.LastChange = 41258.560794039400000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    Left = 496
    Top = 288
  end
  object frxreportxiaopiao: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41257.682618506900000000
    ReportOptions.LastChange = 41729.481567800930000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    ShowProgress = False
    StoreInDFM = False
    Left = 592
    Top = 312
  end
  object frxDBDataset1: TfrxDBDataset
    UserName = 'frxDBDataset1'
    CloseDataSource = False
    DataSet = queryA5
    Left = 32
    Top = 376
  end
  object frxDBA4: TfrxDBDataset
    UserName = 'frxDBA4'
    CloseDataSource = False
    DataSet = queryA4
    Left = 184
    Top = 344
  end
  object queryA5: TADOQuery
    Parameters = <>
    Left = 64
    Top = 328
  end
  object frxReportA5: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41257.682618506900000000
    ReportOptions.LastChange = 41406.584407384260000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    Left = 72
    Top = 176
  end
  object queryA4: TADOQuery
    Parameters = <>
    Left = 128
    Top = 344
  end
end
